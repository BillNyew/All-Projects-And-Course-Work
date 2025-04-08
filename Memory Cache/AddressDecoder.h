#ifndef ADDRESSDECODER_H
#define ADDRESSDECODER_H

class AddressDecoder {
private:
    int setIndexBits;
    int blockOffsetBits;

public:
    AddressDecoder(int setIndexBits, int blockOffsetBits);

    unsigned long getTag(unsigned long address) const;
    unsigned int getSetIndex(unsigned long address) const;
    unsigned int getBlockOffset(unsigned long address) const;
};

#endif
