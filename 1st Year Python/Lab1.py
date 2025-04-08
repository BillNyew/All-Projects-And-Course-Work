def function1(n:int)->int: 
    print("In function1:", n) 
    n = function2(n+1) 
    print("Returned from function2, back in function1", n) 
    return n 
 
def function2(n:int)->int: 
    print("In function2:", n) 
    n = function3(n+1) 
    print("Returned from function3, back in function2", n) 
    return n+1 
 
def function3(n:int)->None: 
    print("In function3:", n) 
    return n+1 
 
def function4(n:int)->int: 
    print("In function4:", n) 
    n = function1(n+1) 
    print("Returned from function1, back in function4", n) 
    return n+1 
 
result = function1(17) 
print(result) 