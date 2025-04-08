def search1(arr:list[int], target:int):
    low = 0
    high = len(arr) - 1
  
    while high - low > 1: # remaining array is larger than 1 element long
        mid = (high + low) // 2 # determine mid point of array
        if arr[mid] < target:
            low = mid + 1 # eliminate left side of array
        else:
            high = mid # eliminate right side of array
  
    if arr[low] == target:
        return low
    elif arr[high] == target:
        return high
    else:
        return -1
def search2(arr:list[int], target:int):
    n = len(arr)
    for i in range(0, n):
        if (arr[i] == target):
            return i
    return -1
if __name__ == '__main__': 
    a = [0, 3, 17, 45, 92, 99, 106, 114, 169, 188, 233]
    target = 79
    result1 = search1(a, target)
    print("search1 result: ")
    if result1 == -1: 
        print("Element " + str(target) + " NOT FOUND in array")
    else: 
        print("Element " + str(target) + " FOUND in array")
    result2 = search2(a, target)
    print("\nsearch2 result: ")
    if result2 == -1: print("Element " + str(target) + " NOT FOUND in array")
    else: print("Element " + str(target) + " FOUND in array")