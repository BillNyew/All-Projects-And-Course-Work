
def some_function( a: int, c: int)->int :
    return a + c//2


number = 10
for i in range(2, 5):
    number =some_function(number,i)
print(number)