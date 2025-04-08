suits=[]
values=[]

poker_hand = [("Ace", "Spades"), ("King", "Hearts"), ("Queen", "Diamonds"), ("Jack", "Hearts"), ("2", "Clubs")]

for element in poker_hand:
    values.append(element[0])
    suits.append(element[1])

print(values)
print(suits)




deck=[]
card_values = ["Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"]
card_suits = ["Spades", "Hearts", "Diamonds", "Clubs"]

for element in card_suits:
    for j in card_values:
        deck.append(element)
        deck.append(j)
print(deck)


