#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define TOKEN_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"
#define HISTORY_SIZE 100

// Global variables for command history
char history[HISTORY_SIZE][BUFFER_SIZE];
int history_count = 0;

// Function prototypes
void print_prompt();
void parse_input(char *input, char **tokens);
int handle_builtin_commands(char **tokens);
void handle_redirection(char **tokens, int *input_redirect, int *output_redirect, char **input_file, char **output_file);
void sigchld_handler(int sig);
void add_to_history(const char *command);
void display_history();
int execute_history_command(const char *command);

int main() {
    char cwd[BUFFER_SIZE];
    char input[BUFFER_SIZE];
    char *tokens[TOKEN_SIZE];
    int input_redirect, output_redirect;
    char *input_file, *output_file;

    // Set up SIGCHLD handler to reap zombie processes
    signal(SIGCHLD, sigchld_handler);

    while (1) {
        // Display the prompt
        print_prompt();

        // Get input from the user
        if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
            perror("fgets");
            continue;
        }

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Add command to history
        add_to_history(input);

        // Check if the command is a history execution command (!n)
        if (execute_history_command(input)) {
            continue;
        }

        // Parse the input into tokens
        parse_input(input, tokens);

        // Check for empty input
        if (tokens[0] == NULL) {
            continue;
        }

        // Handle built-in commands (exit, cd, history)
        if (handle_builtin_commands(tokens)) {
            continue;
        }

        // Check for input and output redirection
        input_redirect = output_redirect = 0;
        input_file = output_file = NULL;
        handle_redirection(tokens, &input_redirect, &output_redirect, &input_file, &output_file);

        // Check if the command should run in the background
        int run_in_background = 0;
        int last_token_index = 0;
        while (tokens[last_token_index] != NULL) {
            last_token_index++;
        }
        if (last_token_index > 0 && strcmp(tokens[last_token_index - 1], "&") == 0) {
            run_in_background = 1;
            tokens[last_token_index - 1] = NULL; // Remove '&' from tokens
        }

        // Fork a new process to execute the command
        pid_t pid = fork();
        if (pid == 0) {
            // Child process

            // Handle input redirection
            if (input_redirect) {
                if (freopen(input_file, "r", stdin) == NULL) {
                    perror("freopen input");
                    exit(EXIT_FAILURE);
                }
            }

            // Handle output redirection
            if (output_redirect) {
                if (freopen(output_file, "w", stdout) == NULL) {
                    perror("freopen output");
                    exit(EXIT_FAILURE);
                }
            }

            // Execute the command
            if (execvp(tokens[0], tokens) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else if (pid > 0) {
            // Parent process
            if (!run_in_background) {
                // Wait for the child process to finish if not in background
                waitpid(pid, NULL, 0);
            }
        } else {
            perror("fork");
        }
    }

    return 0;
}

// Function to print the prompt
void print_prompt() {
    char cwd[BUFFER_SIZE];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s> ", cwd);
        fflush(stdout);
    } else {
        perror("getcwd");
    }
}

// Function to parse input into tokens
void parse_input(char *input, char **tokens) {
    char *token;
    int index = 0;

    token = strtok(input, TOKEN_DELIMITERS);
    while (token != NULL) {
        tokens[index++] = token;
        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    tokens[index] = NULL;
}

// Function to handle built-in commands
int handle_builtin_commands(char **tokens) {
    if (strcmp(tokens[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(tokens[0], "cd") == 0) {
        if (tokens[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(tokens[1]) != 0) {
            perror("cd");
        }
        return 1;
    } else if (strcmp(tokens[0], "history") == 0) {
        display_history();
        return 1;
    }
    return 0;
}

// Function to handle input and output redirection
void handle_redirection(char **tokens, int *input_redirect, int *output_redirect, char **input_file, char **output_file) {
    for (int i = 0; tokens[i] != NULL; i++) {
        if (strcmp(tokens[i], "<") == 0) {
            *input_redirect = 1;
            *input_file = tokens[i + 1];
            tokens[i] = NULL; // Remove the redirection operator and file name
        } else if (strcmp(tokens[i], ">") == 0) {
            *output_redirect = 1;
            *output_file = tokens[i + 1];
            tokens[i] = NULL; // Remove the redirection operator and file name
        }
    }
}

// Signal handler for SIGCHLD
void sigchld_handler(int sig) {
    // Reap all finished child processes
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

// Function to add a command to the history
void add_to_history(const char *command) {
    if (history_count < HISTORY_SIZE) {
        strncpy(history[history_count++], command, BUFFER_SIZE - 1);
    }
}

// Function to display the history
void display_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d %s\n", i + 1, history[i]);
    }
}

// Function to execute a command from history
int execute_history_command(const char *command) {
    if (command[0] == '!' && isdigit(command[1])) {
        int history_index = atoi(&command[1]) - 1;
        if (history_index < 0 || history_index >= history_count) {
            fprintf(stderr, "No such command in history.\n");
            return 1;
        }
        printf("Executing: %s\n", history[history_index]);

        // Parse and execute the command
        char history_command[BUFFER_SIZE];
        strncpy(history_command, history[history_index], BUFFER_SIZE - 1);

        // New array for parsed tokens
        char *tokens[TOKEN_SIZE];
        parse_input(history_command, tokens);

        // Execute the parsed command
        if (handle_builtin_commands(tokens)) {
            return 1;
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Child process: execute the command
            if (execvp(tokens[0], tokens) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else if (pid > 0) {
            // Parent process: wait for the child to finish
            waitpid(pid, NULL, 0);
        } else {
            perror("fork");
        }

        return 1;
    }
    return 0;
}
