def max(some_list: list)-> int:
  max = some_list[0][0]
  for row in some_list:
    for value in row:
      if value > max:
          max = value
  return max

nested_list = [[j * 2 + i+1 for i in range(2)]for j in range(2)]
scaled = []

for row in nested_list:
    scaled_row = []
    for value in row:
        highest_score = max(nested_list)
        scaled_row.append(value/ highest_score)
    scaled.append(scaled_row)
print(nested_list)
print(scaled)

    