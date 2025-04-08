#Gives us the first and last element of the list or variable

def first_and_last(mystring:str) -> tuple:
    first = mystring[0]
    last = mystring[-1]
    return (first, last)

print( first_and_last("hello world!"))
