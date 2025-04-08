import numpy as np
from random import randint, seed

seed(13)
numbers = np.zeros(100, dtype=int)

for i in range(10):
    numbers[i+1] = randint(1, 100)

for i in range(10, 0, -1):
    numbers[i] = numbers[i-1]
numbers[0] = 0
print(numbers)

