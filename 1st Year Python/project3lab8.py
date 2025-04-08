import matplotlib as plt
N=10
keys=[i for i in range(10)]

def bad(key,N):
    return 0
def simplest_hash (key, N):
    hash_code=keys
    return hash_code % N

def simple_hash(key,N):
    hash_code=0
    while key > 0:
        hash_code +=key%N
        key //=N
    return hash_code %N

def plot(function,key,N):
    




 n=2   
plot(simplest_hash, keys, N)