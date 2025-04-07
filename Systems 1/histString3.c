#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* word;
    int frequency;
} Histogram;

char** readWords(int *count) {
    char** words = malloc(100 * sizeof(char*)); // Allocate memory for the words array
    if (!words) {
        printf("Words is NULL\n");
        return NULL; // Exit the program if memory allocation fails
    }
    *count = 0;
    while (scanf("%ms", &words[*count]) != EOF) {
        (*count)++;
    }
    return words;
}
void displayWords(char** words, int count) {
    for (int i = 0; i < count; i++) {
        printf("word %d: %s\n", i, words[i]);
    }
}
Histogram* calculateHistogram(char** words, int count, int *histogramCount) {
    // Allocate memory for the histogram array
    Histogram* histogram = malloc(count * sizeof(Histogram));
    if (!histogram) {
        printf("Histogram is NULL\n");
        return NULL; // Exit the program if memory allocation fails
    }
    *histogramCount = 0; // Initialize histogram count to 0
    for (int i = 0; i < count; i++) {
        int found = 0; // Flag to check if word is already in histogram
        for (int j = 0; j < *histogramCount; j++) {
            if (strcmp(words[i], histogram[j].word) == 0) {
                histogram[j].frequency++; // Increment frequency if word already exists
                found = 1;
                break;
            }
        }
        if (!found) {
            histogram[*histogramCount].word = malloc(strlen(words[i]) + 1); // Add new word to histogram
            strcpy(histogram[*histogramCount].word, words[i]);
            histogram[*histogramCount].frequency = 1; // Initialize frequency to 1
            (*histogramCount)++; // Increment histogram count
        }
    }
    return histogram; // Return pointer to histogram array
}

void displayHistogram(Histogram *histogram, int histogramCount) {
    for (int i = 0; i < histogramCount; i++) {
        printf("word %s: freq %d\n", histogram[i].word, histogram[i].frequency);
    }
}
void sortHistogram(Histogram *histogram, int histogramCount) { //Selection sort
    for (int i = 0; i < histogramCount - 1; i++) {
        for (int j = i + 1; j < histogramCount; j++) {
            if (histogram[j].frequency > histogram[i].frequency) {
                Histogram temp = histogram[i];
                histogram[i] = histogram[j];
                histogram[j] = temp;
            }
        }
    }
}
int main() {
    int count;
    char** words = readWords(&count);
    int histogramCount;
    Histogram* histogram = calculateHistogram(words, count, &histogramCount);
    sortHistogram(histogram, histogramCount);
    displayHistogram(histogram, histogramCount);
    // Free dynamically allocated memory
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
    for (int i = 0; i < histogramCount; i++) {
        free(histogram[i].word);
    }
    free(histogram);
    return 0;
}