#ifndef PERFORMANCECOUNTER_H
#define PERFORMANCECOUNTER_H

class PerformanceCounter {
private:
    int accesses;
    int hits;
    int misses;
    int writebacks;

public:
    PerformanceCounter();
    void incrementAccesses();
    void incrementHits();
    void incrementMisses();
    void incrementWritebacks();

    int getHits() const;
    int getMisses() const;
    int getWritebacks() const;
    float getMissPercentage() const;
    float getWritebackPercentage() const;

    void display() const;
};

#endif
