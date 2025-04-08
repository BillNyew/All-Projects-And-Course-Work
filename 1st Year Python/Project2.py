"""
    Filename: Project2.py
    Author: Bill Turbadrakh
    Date: January 17, 2023
    Course: Intro to Programming II
    Assignment: Project 2 Wordle
    Collaborators: None
    Internet Source: None
"""
from random import randint
with open("usaWords.txt") as words:
    five_letter_words = []
    for line in words:
        line = line.strip()
        if len(line) == 5:
            five_letter_words.append(line)
random_word = five_letter_words[randint(0,len(five_letter_words)-1)]
def print_yellow(s, end='\n'):
   print('\u001b[43;1m', end='')
   print(s, end=end)
   print('\033[0m', end='')
def print_grey(s, end='\n'):
   print('\u001b[47;1m', end='')
   print(s, end=end)
   print('\033[0m', end='')
def print_green(s, end='\n'):
   print('\u001b[42;1m', end='')
   print(s, end=end)
   print('\033[0m', end='')
correct = False
guess_count = 0
while not correct:
    if guess_count >= 6:
        correct = True
        print()
        print(f'The correct word is "{random_word}", please try again.')
        break
    guess = input("Enter a five letter word: ")
    guess_count += 1
    green_count = 0
    for guess_character,word_character in zip(guess,random_word):
        if (len(guess) < 5 or len(guess) > 5) or (guess not in five_letter_words):
            print("You must enter a five letter word!")
            guess_count -= 1
            break
        if guess_character == word_character:
            green_count += 1
            print_green(guess_character,end=' ')
            if green_count == 5:
                print(f'You got it in {guess_count} tries!')
                correct = True
                break
        elif guess_character in random_word and guess_character != word_character:
            print_yellow(guess_character, end = ' ')
        if guess_character not in random_word:
            print_grey(guess_character,end=' ')
    print()