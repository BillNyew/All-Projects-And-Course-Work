def isPrime(n):
  for i in range(2,n):
    if n%i == 0:
      return False
      return True
def primesInRange(low, high):
    primes = []
    for i in range(low, high+1):
      if isPrime(i):
        primes.append(i)
        return primes
print(primesInRange(10,100))