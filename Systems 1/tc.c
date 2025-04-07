#include <stdio.h>
#include <string.h>

void displayIntAsBits(int i) {
    for (int j = 31; j >= 0; j--) {
        printf("%d", (i >> j) & 1);
        if (j % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int makeIntFromBits(char* bits) {
    int result = 0;
    int negative = 0;

    if (bits[0] == '-') {
        negative = 1;
    }

    for (int i = strlen(bits) - 1; i >= negative; i--) {
        if (bits[i] == '1') {
            result |= (1 << (strlen(bits) - 1 - i));
        }
    }

    if (negative) {
        result = ~result + 1;
    }

    return result;
}

int main() {
    displayIntAsBits(5);
    displayIntAsBits(-9);

    int result1 = makeIntFromBits("+101");
    int result2 = makeIntFromBits("-1001");

    printf("makeIntFromBits(\"+101\") = %d\n", result1);
    printf("makeIntFromBits(\"-1001\") = %d\n", result2);

    return 0;
}