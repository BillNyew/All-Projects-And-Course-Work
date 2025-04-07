import sympy

def find_n_for_speedup(target_speedup):
    product = 1
    n = 0
    
    for prime in sympy.primerange(2, 100):
        product *= (1 - 1/prime)
        n += 1
        if 1 / product >= target_speedup:
            break
    
    return n

n = find_n_for_speedup(10)
print(f"n = {n}")
