name_data = {}
with open("yob2021.txt", "r") as file:
    for line in file:
        info_for_name = line.rstrip().split(",")
        name = info_for_name[0]
        frequency = info_for_name[2]
        if name in name_data:
            name_data[name]+=int(frequency)
        else:
            name_data[name]=int(frequency)

print(name_data)