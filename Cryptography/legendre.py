def legendre_symbol(a, p):
    """ Compute the Legendre symbol a|p using Euler's criterion. p is a prime, a is an integer. """
    return pow(a, (p - 1) // 2, p)

def modular_sqrt(a, p):
    """ Find a quadratic residue (mod p) using the Tonelli-Shanks algorithm. p must be an odd prime. """
    if legendre_symbol(a, p) != 1:
        return None  # a is not a quadratic residue modulo p

    if a == 0:
        return (0, 0)
    if p == 2:
        return (a, a)

    # Check if p % 4 == 3 and use the simple method
    if p % 4 == 3:
        r = pow(a, (p + 1) // 4, p)
        return (r, p - r)

    # Factor out powers of 2 from p - 1, so p - 1 = q * 2^s
    s = 0
    q = p - 1
    while q % 2 == 0:
        s += 1
        q //= 2

    # Find a non-residue z
    z = 2
    while legendre_symbol(z, p) != -1:
        z += 1

    # Initializations
    m = s
    c = pow(z, q, p)
    t = pow(a, q, p)
    r = pow(a, (q + 1) // 2, p)

    while t != 0 and t != 1:
        t2i = t
        i = 0
        for i in range(1, m):
            t2i = pow(t2i, 2, p)
            if t2i == 1:
                break

        b = pow(c, 2 ** (m - i - 1), p)
        m = i
        c = pow(b, 2, p)
        t = (t * c) % p
        r = (r * b) % p

    return (r, p - r)

# Given values
a = 2123
p = 4831

# Calculate the square roots
roots = modular_sqrt(a, p)

if roots is None:
    print(f"{a} is not a quadratic residue modulo {p}")
else:
    print(f"The square roots of {a} modulo {p} are: {roots[0]} and {roots[1]}")
