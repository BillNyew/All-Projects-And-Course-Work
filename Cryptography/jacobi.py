
# def jacobi(a, m):
#     if m <= 0 or m % 2 == 0:
#         raise ValueError("m must be a positive odd number")
#     result = 1
#     a = a % m
#     while a != 0:
#         while a % 2 == 0:
#             a = a // 2
#             if m % 8 in [3, 5]:
#                 result = -result
#         a, m = m, a  # swap a and m
#         if a % 4 == 3 and m % 4 == 3:
#             result = -result
#         a = a % m
#     return result if m == 1 else 0

# # Example usage
# a = 10
# m = 21
# print(f"Jacobi symbol (a/m) = ({a}/{m}) is {jacobi(a, m)}")
def jacobisymbol(a, m):
    if m <= 0 or m % 2 == 0:
        raise ValueError("m must be a positive odd number.")
    if a == 0:
        return 0 if m != 1 else 1
    if a == 1:
        return 1
    
    a = a % m
    result = 1
    
    while a != 0:
        while a % 2 == 0:
            a = a // 2
            if m % 8 in [3, 5]:
                result = -result
        
        a, m = m, a  # Swap a and m
        
        if a % 4 == 3 and m % 4 == 3:
            result = -result
        
        a = a % m
    
    return result if m == 1 else 0

# Example usage:
a = 10
m = 3
print(f"The Jacobi symbol ({a}/{m}) is {jacobisymbol(a, m)}")
