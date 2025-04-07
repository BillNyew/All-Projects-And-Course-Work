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

int not_gate(int a) {
    return nand(a, a);
}

int and_gate(int a, int b) {
    return nand(nand(a, b), nand(a, b));
}

int or_gate(int a, int b) {
    return nand(nand(a, a), nand(b, b));
}

int xor_gate(int a, int b) {
    return nand(nand(a, nand(a, b)), nand(b, nand(a, b)));
}

// Helper function to convert decimal to binary representation
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

// Helper function to convert binary representation to decimal
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
    *sum = xor_gate(a, b);
    *carry = and_gate(a, b);
}

void full_adder(int a, int b, int carry_in, int* sum, int* carry_out) {
    int sum1, carry1, sum2, carry2;

    half_adder(a, b, &sum1, &carry1);
    half_adder(sum1, carry_in, &sum2, &carry2);

    *sum = sum2;
    *carry_out = or_gate(carry1, carry2);
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

void testBasicGates() {
    printf("NAND GATE\n");
    printf("nand(0, 0) = %d\n", nand(0, 0));
    printf("nand(0, 1) = %d\n", nand(0, 1));
    printf("nand(1, 0) = %d\n", nand(1, 0));
    printf("nand(1, 1) = %d\n\n", nand(1, 1));

    printf("NOT GATE\n");
    printf("not(0) = %d\n", not_gate(0));
    printf("not(1) = %d\n\n", not_gate(1));

    printf("AND GATE\n");
    printf("and(0, 0) = %d\n", and_gate(0, 0));
    printf("and(0, 1) = %d\n", and_gate(0, 1));
    printf("and(1, 0) = %d\n", and_gate(1, 0));
    printf("and(1, 1) = %d\n\n", and_gate(1, 1));

    printf("OR GATE\n");
    printf("or(0, 0) = %d\n", or_gate(0, 0));
    printf("or(0, 1) = %d\n", or_gate(0, 1));
    printf("or(1, 0) = %d\n", or_gate(1, 0));
    printf("or(1, 1) = %d\n\n", or_gate(1, 1));

    printf("XOR GATE\n");
    printf("xor(0, 0) = %d\n", xor_gate(0, 0));
    printf("xor(0, 1) = %d\n", xor_gate(0, 1));
    printf("xor(1, 0) = %d\n", xor_gate(1, 0));
    printf("xor(1, 1) = %d\n\n", xor_gate(1, 1));
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
    testBasicGates();

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