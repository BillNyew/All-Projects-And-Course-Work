#Average of a list

def average(any_list:list) -> float:
    t = 0
    c = 0
    for e in any_list:
        t = t + e
        c = c + 1
    return t/c 
print(average([1,2,3,4,5]))