Bill Bilguun Turbadrakh-873631681
Systems 2
Prof. Stevenson
1/27/25


This project is a mini Linux shell implemented in C.
It’s designed to act as a simple but functional shell environment where users can execute basic commands, redirect input and output, run background processes, and even keep track of previously executed commands.
The shell operates in a loop, displaying the current working directory as part of the prompt, and waits for the user to enter a command.
It handles built-in commands like cd for changing directories and exit to close the shell, as well as external commands that are executed through the fork and execvp system calls.
One of the key features of this shell is its ability to manage background processes.
If the user adds an & to the end of a command, the shell will execute that command in the background and return immediately to accept more input. 
To prevent zombie processes from lingering, a SIGCHLD handler is implemented, which cleans up terminated child processes automatically.
This ensures the shell runs smoothly without leaving any unnecessary processes hanging around.
The shell also supports input and output redirection. 
By using < to redirect input from a file or > to redirect output to a file, users can easily control where data comes from or goes.
For example, running ls -l > output.txt will save the output of the ls command into a file named output.txt.
The redirection tokens and filenames are processed and removed from the command line before execution, so the underlying command works as expected.
For added convenience, the shell includes a history feature that keeps track of up to 100 previously executed commands.
Users can view the command history by typing history, and they can re-run a specific command using !n, where n is the command’s number in the history list.
This makes it easy to repeat complex or frequently used commands without retyping them.
Testing the shell involved running a variety of commands to ensure everything worked as expected.
Commands like ls and pwd executed correctly, and built-in commands like cd handled both valid and invalid inputs gracefully. 
Redirection was tested by saving command output to files and feeding input from files. 
Background processes were verified with long-running commands like sleep 5 &, and no zombie processes were observed.
The history feature was also tested extensively, including edge cases like invalid history references, and it performed as intended.
To run this shell, you can compile the program with gcc -o shell shell.c and then start it by running ./shell. 
From there, you can try out basic commands, experiment with input and output redirection, run background processes, and test the history feature.