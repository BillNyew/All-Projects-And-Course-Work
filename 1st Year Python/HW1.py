def transpose(list_1, list_2):
    list_2 =[[row[i] for row in list_1] for i in range(len(list_1[0]))]
    return list_2

list_1 = [[ 1, 2, 3, 4], [5, 6, 7, 8]]
list_2 = []
print(transpose(list_1, list_2))
