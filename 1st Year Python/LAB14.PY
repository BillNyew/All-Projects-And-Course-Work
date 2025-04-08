def contains(list: list,num: int)-> bool:
    for element in list:
        if element == num:
            return True
    return False

assert contains([1, 5, 2, 6, 9, 0], 5)==True, "5 is in the list"
assert contains([1, 10, 2, 6, 9, 0], 5)==False, "5 is not in the list"
assert contains([5, 1, 2, 6, 9], 5)==True, "5 is in the list"
assert contains([1, 2, 6, 9, 5], 5)==True, "5 is in the list"
assert contains([], 5)==False, "5 is not in an empty list"
print("All tests passed!")
