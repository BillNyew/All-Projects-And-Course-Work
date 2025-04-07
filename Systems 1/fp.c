#include <stdio.h>
#include <string.h>

typedef union floatU {
    unsigned int bits;
    float theFloat;
} floatU;

void displayFloatAsBits(float f) {
    floatU fu;
    fu.theFloat = f;
    unsigned int value = fu.bits;
    for (int i = 31; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i == 31 || i == 23) {
            printf(" ");
        }
    }
    printf("\n");
}

float makeFloatFromBits(char* f) {
    int sign = (f[0] == '-') ? 1 : 0;
    int dotIndex = 0;
    for (int i = 0; f[i] != '\0'; i++) {
        if (f[i] == '.') {
            dotIndex = i;
            break;
        }
    }
    
    int exponent = dotIndex - 1;
    unsigned int mantissa = 0;
    int exponentBias = 127;

    for (int i = 1; f[i] != '\0'; i++) {
        if (f[i] != '.') {
            mantissa = (mantissa << 1) | (f[i] - '0');
        }
    }

    unsigned int bits = 0;
    bits |= (sign << 31);
    bits |= ((exponent + exponentBias) << 23);
    bits |= (mantissa & 0x7FFFFF);

    floatU fu;
    fu.bits = bits;

    return fu.theFloat;
}

int main() {
    float result = makeFloatFromBits("-101.1101");
    printf("makeFloatFromBits(\"-101.1101\") = %f\n", result);
    
    printf("displayFloatAsBits(-5.8125):\n");
    displayFloatAsBits(-5.8125);

    return 0;
}