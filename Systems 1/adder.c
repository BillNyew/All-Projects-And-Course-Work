#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Basic Gates
int nand(int a, int b) {
    if (a == 1 && b == 1) {
        return 0;
    }
    return 1;
}

int* getBits(char num) {
    int* bits = (int*)malloc(8 * sizeof(int));
    if (num >= 0) {
        bits[0] = 0;
    } else {
        bits[0] = 1;
        num = -num;
    }
    for (int i = 7; i >= 1; i--) {
        bits[i] = num % 2;
        num /= 2;
    }
    return bits;
}

char getInt(int* bits) {
    char num = 0;
    int sign = bits[0] ? -1 : 1;
    for (int i = 1; i < 8; i++) {
        num += bits[i] * pow(2, 7 - i);
    }
    return num * sign;
}

// Adders
void half_adder(int a, int b, int* sum, int* carry) {
    *sum = nand(nand(a, b), nand(a, b));
    *carry = nand(nand(a, b), b);
}

void full_adder(int a, int b, int carry_in, int* sum, int* carry_out) {
    int sum1, carry1, sum2, carry2;

    half_adder(a, b, &sum1, &carry1);
    half_adder(sum1, carry_in, &sum2, &carry2);

    *sum = sum2;
    *carry_out = carry2;
}

void eight_bit_adder(int a[], int b[], int sum[]) {
    int carry = 0;

    full_adder(a[0], b[0], carry, &sum[0], &carry);
    full_adder(a[1], b[1], carry, &sum[1], &carry);
    full_adder(a[2], b[2], carry, &sum[2], &carry);
    full_adder(a[3], b[3], carry, &sum[3], &carry);
    full_adder(a[4], b[4], carry, &sum[4], &carry);
    full_adder(a[5], b[5], carry, &sum[5], &carry);
    full_adder(a[6], b[6], carry, &sum[6], &carry);
    full_adder(a[7], b[7], carry, &sum[7], &carry);

    sum[8] = carry; // Store final carry in sum[8]
}

void printBits(int* bits, int num) {
    printf("%d%d%d%d%d%d%d%d --> %d\n", bits[0], bits[1], bits[2], bits[3], bits[4], bits[5], bits[6], bits[7], num);
}

void testAddition(char num1, char num2) {
    int* bits1 = getBits(num1);
    int* bits2 = getBits(num2);
    int sum[9];

    eight_bit_adder(bits1, bits2, sum);

    printBits(bits1, num1);
    printBits(bits2, num2);
    printf("-----------------\n");
    int sum_decimal = num1 + num2;
    int* sum_bits = getBits(sum_decimal);
    printBits(sum_bits, sum_decimal);

    free(bits1);
    free(bits2);
    free(sum_bits);
}

int main() {
    // Test case 1: 120 + 5
    testAddition(120, 5);
    printf("\n");

    // Test case 2: 120 + (-5)
    testAddition(120, -5);
    printf("\n");

    // Test case 3: 120 + 8
    testAddition(120, 8);
    printf("\n");

    // Test case 4: -120 + (-9)
    testAddition(-120, -9);
    printf("\n");

    return 0;
}