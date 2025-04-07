#include <stdio.h>

// Helper function to print an array of bits
void printBits(int* bits) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", bits[i]);
    }
}

// Function to convert a decimal number to an array of 8 bits
void getBits(char num, int* bits) {
    for (int i = 0; i < 8; i++) {
        bits[i] = (num >> i) & 1;
    }
}

// Function to convert an array of 8 bits to a decimal number
char getInt(int* bits) {
    char num = 0;
    for (int i = 0; i < 8; i++) {
        num += bits[i] << i;
    }
    return num;
}

int main() {
    int sum[8], a[8], b[8];

    // Test 1: 120 + 5
    getBits(120, a);
    getBits(5, b);
    eight_bit_adder(a, b, sum);
    printf("120 --> ");
    printBits(a);
    printf(" --> %d\n", 120);
    printf("5 --> ");
    printBits(b);
    printf(" --> %d\n", 5);
    printf("-----------------\n");
    printf("sum --> ");
    printBits(sum);
    printf(" --> %d\n", getInt(sum));

    // Test 2: 120 + (-5)
    getBits(-5, b);
    eight_bit_adder(a, b, sum);
    printf("120 --> ");
    printBits(a);
    printf(" --> %d\n", 120);
    printf("-5 --> ");
    printBits(b);
    printf(" --> %d\n", -5);
    printf("-----------------\n");
    printf("sum --> ");
    printBits(sum);
    printf(" --> %d\n", getInt(sum));

    // Test 3: 120 + 8
    getBits(8, b);
    eight_bit_adder(a, b, sum);
    printf("120 --> ");
    printBits(a);
    printf(" --> %d\n", 120);
    printf("8 --> ");
    printBits(b);
    printf(" --> %d\n", 8);
    printf("-----------------\n");
    printf("sum --> ");
    printBits(sum);
    printf(" --> %d\n", getInt(sum));

    // Test 4: -120 + (-9)
    getBits(-120, a);
    getBits(-9, b);
    eight_bit_adder(a, b, sum);
    printf("-120 --> ");
    printBits(a);
    printf(" --> %d\n", -120);
    printf("-9 --> ");
    printBits(b);
    printf(" --> %d\n", -9);
    printf("-----------------\n");
    printf("sum --> ");
    printBits(sum);
    printf(" --> %d\n", getInt(sum));

    return 0;
}