if __name__ == '__main__':
    # Part 1. Use list comprehension to create a list containing the first 500 multiples of 5.
    # (The first element should be 5, the last element should be 2500)
    multiples_of_five = []  
for i in range(1, 25001): 
    if i%5==0: 
        multiples_of_five.append(i) 
    # Part 2. The list below gives the most popular baby names in 2021 that start with the letter 'E'
    # Create a new list that contains all the elements in the original list, but converted to lower-case.
    # Use list comprehension to do this.
    popular_E_names = ['Emma', 'Evelyn', 'Elizabeth', 'Eleanor', 'Ella', 'Emily', 'Ellie', 'Emilia', 'Eliana', 'Everly', 'Elena', 'Emery', 'Eva', 'Everleigh', 'Eloise', 'Eliza', 'Eden', 'Elliana', 'Elijah', 'Ethan', 'Ezra', 'Elias', 'Ezekiel', 'Eli', 'Easton', 'Everett', 'Emmett', 'Evan', 'Enzo', 'Elliot', 'Elliott', 'Emiliano']
    popular_e_names = []

    [x.lower() for x in ['E']]
['e']
    
    #Part 3: Using the original list of (capitalized) popular E-names in part 2, use list comprehension
    # this time to create a new list of the nams that start with "Em". Note that you will need to use 
    # a conditional list comprehension.
    
    
print(multiples_of_five)
print(popular_e_names)
    
   