from pprint import pprint

f = open("list_of_metals.txt", 'r')

metal_dict = {}

for line in f:
    inner = []
    for line in f:
        x = line.strip().split(":")
        left = x[0].lower()
        right = x[1]
        metal_dict[left] = right

user = input("What metal would you like to look up? enter 'quit' to stop: ")
user = user.lower()

if user in metal_dict:
    print(metal_dict[user])

while user not in metal_dict:
    if user == quit:
        break

    print("Metal does not exsist")
    user = input("What metal would you like to look up? enter 'quit' to stop: ")
    user = user.lower()
    if user in metal_dict:

        print(metal_dict[user])

while user != quit:
    user = input("What metal would you like to look up? enter 'quit' to stop: ")
    user = user.lower()
    if user == quit:
        break

    
    while user not in metal_dict:
        if user == quit:
            break

    
        print("Metal does not exsist")

        user = input("What metal would you like to look up? enter 'quit' to stop: ")
        user = user.lower()
        if user in metal_dict:
            print(metal_dict[user])


    if user in metal_dict:
        print(metal_dict[user])
