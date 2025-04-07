#include <stdio.h>

// Basic Gates

int nand(int a, int b) {
    if (a == 1) {
        if (b == 1) {
            return 0;  // return 0 if a and b are 1
        }
    }
    return 1; // return 1 in all other cases
}

int not(int a) {
    return nand(a, a);
}

int and(int a, int b) {
    return nand(nand(a, b), nand(a, b));
}

int or(int a, int b) {
    return nand(nand(a, a), nand(b, b));
}

int xor(int a, int b) {
    return nand(nand(a, nand(a, b)), nand(b, nand(a, b)));
}

// Adders

void half_adder(int a, int b, int* sum, int* carry) {
    *sum = nand(nand(a, nand(a, b)), nand(b, nand(a, b)));
    *carry = nand(a, b);
}

void full_adder(int a, int b, int carry_in, int* sum, int* carry_out) {
    int s1, c1, c2;
    half_adder(a, b, &s1, &c1);
    half_adder(s1, carry_in, sum, &c2);
    *carry_out = nand(nand(c1, c2), nand(s1, carry_in));
}

void eight_bit_adder(int a[], int b[], int sum[]) {
    int carry1, carry2, carry3, carry4, carry5, carry6, carry7;

    // First full adder
    full_adder(a[7], b[7], 0, &sum[7], &carry1);

    // Second full adder
    full_adder(a[6], b[6], carry1, &sum[6], &carry2);

    // Third full adder
    full_adder(a[5], b[5], carry2, &sum[5], &carry3);

    // Fourth full adder
    full_adder(a[4], b[4], carry3, &sum[4], &carry4);

    // Fifth full adder
    full_adder(a[3], b[3], carry4, &sum[3], &carry5);

    // Sixth full adder
    full_adder(a[2], b[2], carry5, &sum[2], &carry6);

    // Seventh full adder
    full_adder(a[1], b[1], carry6, &sum[1], &carry7);

    // Eighth full adder
    full_adder(a[0], b[0], carry7, &sum[0], &sum[8]);
}

// Conversion functions

void getBits(char num, int* bits) {
    for (int i = 0; i < 8; i++) {
        bits[i] = (num >> i) & 1;
    }
}

char getInt(int* bits) {
    char num = 0;
    for (int i = 0; i < 8; i++) {
        num += bits[i] << i;
    }
    return num;
}

// Main function for testing

int main() {
    int sum[8], a[8], b[8];

    // Test 1: 120 + 5
    getBits(120, a);
    getBits(5, b);
    eight_bit_adder(a, b, sum);
    printf("120 --> ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", a[i]);
    }
    printf(" --> %d\n", 120);
    printf("5 --> ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", b[i]);
    }
    printf(" --> %d\n", 5);
    printf("-----------------\n");
    printf("sum --> ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", sum[i]);
    }
    printf(" --> %d\n", getInt(sum));

    // Additional tests can be added here

    return 0;
}