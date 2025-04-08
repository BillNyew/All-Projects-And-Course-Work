"""
code allows for user to input meters and converts it to feet and inches

File Name:bill_turbadrakhproject7.py
Author:Bill Turbadrakh
Date: 10/28/22
Course:COMP 1351-6
Assignment:Project 7
Collaborators:
Internet Source:

"""
print("Take an amount of candy from one of the six boxes. The last person to take candy wins.")
 
#creates list
boxes = []
for i in range(1, 7):
    boxes.append(7)
p1 = input("Player 1 input name:")
p2 = input("Player 2 input name: ")
 
#displays game by printing values on the same line
def display_game(l: list):
    print("-----   -----   -----   -----   -----   -----")
    for i in range(0, len(l)):
        print("|", l[i],  "|", end ="   ")
    print()
    print("-----   -----   -----   -----   -----   -----")
display_game(boxes)
 
#chekcs to see if the last person who took it made all boxes zero, and wins the game
def checkWinner(l: list):
    c = 0
    for element in l:
        if element == 0:
            c += 1
    if c == len(l):
        return True
    else:
        return False
 
player1 = 1
player2 = 0
p1W = False
p2W = False
 
#while loop using a value that changes at the end of the players turn
while checkWinner(boxes) == False:
    if player1 == 1:
        #used to index through box values
        box_choose = int(input(f"{p1} choose a box to take candy from: "))
        #if the user puts in an invalid box number an error message will show
        while box_choose < 1 or box_choose > 6:
            print("Error: Not a valid box number. Enter a new number")
            box_choose = int(input("Choose a box to take candy from: "))
        box_choose -= 1
        #ensures players cant choose boxes with no candy
        if boxes[box_choose] == 0:
            print("No more candy left in box. Choose new box")
            box_choose = int(input(f"{p1} choose a box to take candy from: "))
        candy_choose = int(input(f"Enter number of candy to take from the box: "))
        #makes sure candy is within limits
        while candy_choose < 1 or candy_choose > 7:
            print("Error not a valid candy number. Enter a new number")
            candy_choose = int(input(f"Enter number of candy to take from the box: "))
            #if the amount would cause the candy to be in the negatives, it is an invalid number
        if boxes[box_choose] - candy_choose == -1:
            print("Error. Not enough candy in box.")
            print("Error not a valid candy number. Enter a new number")
            candy_choose = int(input(f"Enter number of candy to take from the box: "))
        #updates candy value
        boxes[box_choose] -= candy_choose
        display_game(boxes)
        #if the player made the boxes all 0, then their value is updated to true to represent winning
        if checkWinner(boxes):
            p1W = True
        #updates values to have player2s loop play
        player2 += 1
        player1 -= 1
    #same as pervious loop, for player 2
    if player2 == 1:
        box_choose = int(input(f"{p2} choose a box to take candy from: "))
 
        while box_choose < 1 or box_choose > 6:
            print("Error: Not a valid box number. Enter a new number")
            box_choose = int(input("Choose a box to take candy from: "))
        box_choose -= 1
        if boxes[box_choose] == 0:
            print("No more candy left in box. Choose new box")
            box_choose = int(input(f"{p2} choose a box to take candy from: "))
        candy_choose = int(input(f"Enter number of candy to take from the box: "))
        while candy_choose < 1 or candy_choose > 7:
            print("Error not a valid candy number. Enter a new number")
            candy_choose = int(input(f"Enter number of candy to take from the box: "))
        if boxes[box_choose] - candy_choose == -1:
            print("Error. Not enough candy in box.")
            print("Error not a valid candy number. Enter a new number")
            candy_choose = int(input(f"Enter number of candy to take from the box: "))
 
        boxes[box_choose] -= candy_choose
        display_game(boxes)
        if checkWinner(boxes) == True:
            p2W = True
        #updates values to have player 1s turn
        player2 -= 1
        player1 += 1
#using previously mentioned true values, the winner is displayed
if p1W == True:
    print(f"{p1} wins")
else:
    print(f"{p2} wins")