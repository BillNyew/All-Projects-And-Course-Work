#include <stdio.h>

typedef unsigned short bitSet;

bitSet makeBitSet() {
    return 0;
}

void displayBitSet(bitSet bs) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (bs >> i) & 1);
    }
    printf("\n");
}

void setBit(bitSet* bs, int index) {
    *bs |= (1 << index);
}

void clearBit(bitSet* bs, int index) {
    *bs &= ~(1 << index);
}

int bitValue(bitSet bs, int index) {
    return (bs >> index) & 1;
}

int main() {
    bitSet bs = makeBitSet();
    printf("Initial bitset: ");
    displayBitSet(bs);

    setBit(&bs, 3);
    printf("After setting bit 3: ");
    displayBitSet(bs);

    clearBit(&bs, 7);
    printf("After clearing bit 7: ");
    displayBitSet(bs);

    printf("Value of bit 2: %d\n", bitValue(bs, 2));

    return 0;
}