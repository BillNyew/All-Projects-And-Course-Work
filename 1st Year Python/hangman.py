"""
 Filename: hangman.py
 Author: Bill Turbadrakh
 Date: May 11 2023
 Course: COMP 1353
 Assignment: Hangman Part 1
 Collaborators: None
 Internet Source: None
"""
import random

# Read in dictionary file and store words by length
dictionary = {}
with open('dictionary-3.txt', 'r') as file:
    for word in file:
        word = word.strip().lower()
        length = len(word)
        if length not in dictionary:
            dictionary[length] = [word]
        else:
            dictionary[length].append(word)


# Implementation of the hangman
class Hangman:
    def __init__(self, word_length, num_guesses):
        self.word_length = word_length
        self.num_guesses = num_guesses
        self.guessed_letters = set()
        self.chosen_word = random.choice(dictionary[word_length])
        self.current_state = ['_'] * word_length

    def play(self):
        while self.num_guesses > 0:
            print(' '.join(self.current_state))
            print(f'Number of guesses remaining: {self.num_guesses}')

            guess = input('Guess a letter: ').strip().lower()

            if guess in self.guessed_letters:
                print('You already guessed that letter. Guess a different letter.')
                continue

            self.guessed_letters.add(guess)

            if guess in self.chosen_word:
                for i, letter in enumerate(self.chosen_word):
                    if letter == guess:
                        self.current_state[i] = letter
                if '_' not in self.current_state:
                    print('Congratulations, you won!')
                    return

            else:
                self.num_guesses -= 1
                print('Sorry, that letter is not in the word.')

        print(f'Sorry, you lost. The word was {self.chosen_word}.')


class MaliciousHangman(Hangman):
    def __init__(self, word_length, num_guesses):
        self.word_length = word_length
        self.num_guesses = num_guesses
        self.guessed_letters = set()
        self.word_families = self.generate_word_families()
        self.chosen_word = random.choice(dictionary[word_length])
        self.current_state = ['_'] * word_length

    def generate_word_families(self):
        word_families = {}
        for word in dictionary[self.word_length]:
            key = ''.join('_' if letter in self.guessed_letters else letter for letter in word)
            if key not in word_families:
                word_families[key] = [word]
            else:
                word_families[key].append(word)
        return word_families

    def play(self):
        while self.num_guesses > 0:
            print(' '.join(self.current_state))
            print(f'Number of guesses remaining: {self.num_guesses}')

            guess = input('Guess a letter: ').strip().lower()

            if guess in self.guessed_letters:
                print('You already guessed that letter. Guess a different letter.')
                continue

            self.guessed_letters.add(guess)

            word_family = self.word_families[''.join('_' if letter in self.guessed_letters else letter for letter in self.chosen_word)]
            if guess not in self.chosen_word:
                self.num_guesses -= 1
                print('Sorry, that letter is not in the word.')
                self.word_families = self.filter_word_families(self.word_families, guess)
            else:
                self.chosen_word = random.choice(word_family)
                self.current_state = [letter if letter == guess else '_' for letter in self.chosen_word]
                if '_' not in self.current_state:
                    print('Congratulations, you won!')
                    return

        print(f'Sorry, you lost. The word was {self.chosen_word}.')

    def filter_word_families(self, word_families, guess):
        filtered_families = {}
        for key, words in word_families.items():
            if guess not in key:
                filtered_families[key] = words
        return filtered_families