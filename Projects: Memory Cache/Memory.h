#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
    int size;
    unsigned char* bytes;

public:
    Memory(int size);
    ~Memory();

    unsigned char getByte(unsigned long address) const;
    void setByte(unsigned long address, unsigned char value);
    int getSize() const;
    void display() const;
};

#endif
