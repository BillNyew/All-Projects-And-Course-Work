#include <stdio.h>

typedef struct {
    int number;
    int frequency;
} freq;

void readScores(int *scores, int *count) { 
//function takes an array of Coord structures (scores) and a pointer to an integer (count)
    *count = 0;
    while (scanf("%d", &scores[*count]) != EOF) {
        (*count)++;
        //put a pointer from the score to the count
        //count updates with each score read
    }
}
void displayScores(int *scores, int count) {
    for (int i = 0; i < count; i++) {
        //loop that iterates each score in the scores array
        printf("score %d: %d\n", i, scores[i]);
        //displays Coord
    }
}
void calcHistogram(int *scores, int count, freq *histogram, int *histogramCount) {
    *histogramCount = 0;
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < *histogramCount; j++) {
            //This line starts a nested loop that iterates over each entry in the histogram array.
            if (scores[i] == histogram[j].number) {
                histogram[j].frequency++;
                found = 1;//is found
                //this line increments the frequency field of the corresponding freq structure.

                break;
            }
        }
        if (!found) {
            histogram[*histogramCount].number = scores[i];
            histogram[*histogramCount].frequency = 1;
            (*histogramCount)++;
            //If the score was not found, this adds a new entry to the histogram array with the score as the number field and a frequency of 1,
            //then increments the histogramCount variable to indicate that a new score has been added to the histogram.

        }
    }
}
void displayHistogram(freq *histogram, int histogramCount) {
    for (int i = 0; i < histogramCount; i++) {
        printf("value %d: freq %d\n", histogram[i].number, histogram[i].frequency);
    }
}
void sortHistogram(freq *histogram, int histogramCount) {
    for (int i = 0; i < histogramCount - 1; i++) {
        for (int j = i + 1; j < histogramCount; j++) {
            if (histogram[j].frequency > histogram[i].frequency) {
                freq temp = histogram[i];
                histogram[i] = histogram[j];
                histogram[j] = temp;
            }
        }
    }
}
int main() {
    int scores[100];
    int count;
    readScores(scores, &count);
    freq histogram[count];
    int histogramCount;
    calcHistogram(scores, count, histogram, &histogramCount);
    sortHistogram(histogram, histogramCount);
    displayHistogram(histogram, histogramCount);
    return 0;
}







// #include <stdio.h>

// struct coord {
//     int x;
//     int y;
//     int z;
// };

// typedef struct coord Coord;

// void readScores(Coord *scores, int *count) {
//     *count = 0;
//     while (scanf("%d", &scores[*count].x) != EOF) {
//         (*count)++;
//     }
// }

// void displayScores(Coord *scores, int count) {
//     for (int i = 0; i < count; i++) {
//         printf("score %d: %d\n", i, scores[i].x);
//     }
// }

// int main() {
//     Coord scores[100];
//     int count;
//     readScores(scores, &count);
//     displayScores(scores, count);
//     return 0;
// }



// #include <stdio.h>
// struct coord {
//     int x;
//     int y;
//     int z;
// };
// typedef struct coord Coord;
// //Coord = scores
// typedef struct {
//     int number;
//     int frequency;
// } freq;

// void readScores(Coord *scores, int *count) { 
// //function takes an array of Coord structures (scores) and a pointer to an integer (count)
//     *count = 0;
//     while (scanf("%d", &scores[*count].x) != EOF) {
//         (*count)++;
//         //put a pointer from the score to the count
//         //count updates with each score read
//     }
// }
// void displayScores(Coord *scores, int count) {
//     for (int i = 0; i < count; i++) {
//         //loop that iterates each score in the scores array
//         printf("score %d: %d\n", i, scores[i].x);
//         //displays Coord
//     }
// }
// void calcHistogram(Coord *scores, int count, freq *histogram, int *histogramCount) {
//     *histogramCount = 0;
//     for (int i = 0; i < count; i++) {
//         int found = 0;
//         for (int j = 0; j < *histogramCount; j++) {
//             //This line starts a nested loop that iterates over each entry in the histogram array.
//             if (scores[i].x == histogram[j].number) {
//                 histogram[j].frequency++;
//                 found = 1;//is found
//                 //this line increments the frequency field of the corresponding freq structure.

//                 break;
//             }
//         }
//         if (!found) {
//             histogram[*histogramCount].number = scores[i].x;
//             histogram[*histogramCount].frequency = 1;
//             (*histogramCount)++;
//             //If the score was not found, this adds a new entry to the histogram array with the score as the number field and a frequency of 1,
//             //then increments the histogramCount variable to indicate that a new score has been added to the histogram.

//         }
//     }
// }
// void displayHistogram(freq *histogram, int histogramCount) {
//     for (int i = 0; i < histogramCount; i++) {
//         printf("value %d: freq %d\n", histogram[i].number, histogram[i].frequency);
//     }
// }
// int main() {
//     Coord scores[100];
//     int count;
//     readScores(scores, &count);
//     freq histogram[count];
//     int histogramCount;
//     calcHistogram(scores, count, histogram, &histogramCount);
//     displayHistogram(histogram, histogramCount);
//     return 0;
// }
