#include "PerformanceCounter.h"
#include <iostream>

PerformanceCounter::PerformanceCounter() : hits(0), misses(0), writebacks(0) {}

void PerformanceCounter::incrementHits() {
    hits++;
}

void PerformanceCounter::incrementMisses() {
    misses++;
}

void PerformanceCounter::incrementWritebacks() {
    writebacks++;
}

int PerformanceCounter::getHits() const {
    return hits;
}

int PerformanceCounter::getMisses() const {
    return misses;
}

int PerformanceCounter::getWritebacks() const {
    return writebacks;
}

float PerformanceCounter::getMissPercentage() const {
    return (misses + hits) > 0 ? (static_cast<float>(misses) / (misses + hits)) * 100 : 0.0f;
}

float PerformanceCounter::getWritebackPercentage() const {
    return (writebacks + hits + misses) > 0 ? (static_cast<float>(writebacks) / (writebacks + hits + misses)) * 100 : 0.0f;
}

void PerformanceCounter::display() const {
    std::cout << "Accesses:     " << (hits + misses) << std::endl;
    std::cout << "Hits:         " << hits << std::endl;
    std::cout << "Misses:       " << misses << std::endl;
    std::cout << "Writebacks:   " << writebacks << std::endl;
    std::cout << "Miss Perc:    " << getMissPercentage() << std::endl;
    std::cout << "Writeback Perc: " << getWritebackPercentage() << std::endl;
}
