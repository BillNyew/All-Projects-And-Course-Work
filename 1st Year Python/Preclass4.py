from random import random
numbers = [[int(random()*100+1) for col in range(10)] for row in range(5) ]
for i in range(len(numbers)):
    print(numbers[i][0])
    