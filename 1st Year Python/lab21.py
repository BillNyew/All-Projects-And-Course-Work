def modified_selection_sort(numbers):
    n = len(numbers)
    for i in range(n-1, 0, -1):
        max_index = 0
        for j in range(1, i+1):
            if numbers[j] > numbers[max_index]:
                max_index = j
        numbers[max_index], numbers[i] = numbers[i], numbers[max_index]
        print(numbers)
if __name__ == "__main__":
    numbers = [int(number) for number in input().split()]
    modified_selection_sort(numbers)