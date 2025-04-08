#include "AddressDecoder.h"

AddressDecoder::AddressDecoder(int setIndexBits, int blockOffsetBits)
    : setIndexBits(setIndexBits), blockOffsetBits(blockOffsetBits) {}

unsigned long AddressDecoder::getTag(unsigned long address) const {
    return address >> (setIndexBits + blockOffsetBits);
}

unsigned int AddressDecoder::getSetIndex(unsigned long address) const {
    return (address >> blockOffsetBits) & ((1 << setIndexBits) - 1);
}

unsigned int AddressDecoder::getBlockOffset(unsigned long address) const {
    return address & ((1 << blockOffsetBits) - 1);
}
