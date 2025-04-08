"""
code allows for user to input meters and converts it to feet and inches

File Name:
Author:
Date:
Course:COMP 1351-6
Assignment:Project 2
Collaborators:
Internet Source:

"""

meters = float(input("Enter height in meters: "))

feet= int( meters / .3048)
inches= meters / .3048 %1*12
if meters>0:
    print(f"The height of {meters} meters is {feet} feet and {inches} inches")
elif meters<=0:
    print(f"Error Invalid Input")