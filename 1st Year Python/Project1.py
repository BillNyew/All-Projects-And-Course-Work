"""
    Filename: Project1.py
    Author: Bill Turbadrakh
    Date: January 8, 2023
    Course: Intro to Programming II
    Assignment: Project 1 A Guessing Game
    Collaborators: None
    Internet Source: None
"""

from random import randint

answer = False
a =  randint(0,9)
b = randint(0,9)
c = randint(0,9)

while a == b:
    b = randint(0,9)
while  a == c:
    c = randint(0,9)
while b == c:
    c = randint(0,9)

num = (f'{a}{b}{c}')
guess_counter = 0

while not answer:
    guess = int(input("\n What is your guess? "))
    guess_counter += 1
    guess = str(guess)
    bagle_counter = 0
    fermi_coutner = 0
    for guess_character,num_character in zip(guess,num):
        if len(guess) > 3 or len(guess) < 3:
            print("Invaild input. You must enter three unique numbers between 0 and 9")
            guess_counter -= 1
            break
        if guess[0] == guess[1] or guess[1] == guess[2] or guess[2] == guess[0]:
            print("Invaild input. You must enter three unique numbers between 0 and 9")
            guess_counter -= 1
            break
        if guess_character in num:
            if guess_character == num_character:
                print("Fermi!", end = ' ')
                fermi_coutner += 1
                if fermi_coutner == 3:
                    answer = True
                    print("\n Game Over!")
                    print(f'You guess the right number in {guess_counter} attempts!')
                    break
            elif guess_character in num:
                print("Pico!", end=' ')
        if guess_character not in num:
            bagle_counter +=1
            if bagle_counter == 3:
                print("Bagles!", end=' ')
                break
            pass