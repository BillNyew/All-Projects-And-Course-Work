import numpy as np
import time
import random
import matplotlib.pyplot as plt
import pandas as pd
class ArrayListGeometric:
    def __init__(self):
        self.capacity = 10  # initial capacity
        self.size = 0
        self.array = np.empty(self.capacity, dtype=object)
    def get(self, i):
        if i < 0 or i >= self.size:
            raise IndexError('Index out of range')
        return self.array[i]
    def append(self, e):
        if self.size == self.capacity:
            self.expand_array()
        self.array[self.size] = e
        self.size += 1
    def remove(self, i):
        if i < 0 or i >= self.size:
            raise IndexError('Index out of range')
        for j in range(i, self.size - 1):
            self.array[j] = self.array[j + 1]
        self.size -= 1
    def set(self, i, e):
        if i < 0 or i >= self.size:
            raise IndexError('Index out of range')
        self.array[i] = e
    def get_size(self):
        return self.size
    def is_empty(self):
        return self.size == 0
    def expand_array(self):
        self.capacity *= 2
        temp = np.empty(self.capacity, dtype=object)
        for i in range(self.size):
            temp[i] = self.array[i]
        self.array = temp
class ArrayListArithmetic(ArrayListGeometric):
    def expand_array(self):
        self.capacity += 10
        temp = np.empty(self.capacity, dtype=object)
        for i in range(self.size):
            temp[i] = self.array[i]
        self.array = temp
print(f'n\t\telapsed_time\t\truntime')
num_trial = 1 #appropriate value here
for n in (100000, 200000, 400000, 800000):
    start = time.time()
    for j in range(num_trial):
        A = ArrayListGeometric()
       #create ArrayList
        for i in range(n):
            A.append(i)
            #Append n elements
    stop = time.time()
    print(f'{n}\t\t{stop - start}\t\t{(stop - start)/num_trial}')
#The geometric implementation has an amortized O(1) time complexity for append operations, but occasionally may take O(n) time to expand the array.
#The arithmetic implementation has a worst-case O(n) time complexity for expanding the array, but each append operation still takes O(1) time on average.