package HW2;

import java.util.ArrayList;
import java.util.Collections;

public class Deck {
    // Private instance variable to hold a list of cards in the deck
    private ArrayList<Card> cards;

    // Constructor to initialize a full deck of cards
    public Deck() {
        cards = new ArrayList<Card>();
        // Populate the deck with all 52 cards (4 suits, ranks 2-14)
        for (char suit : new char[] { 'c', 'd', 'h', 's' }) {
            for (int rank = 2; rank <= 14; rank++) {
                cards.add(new Card(rank, suit));
            }
        }
    }

    // Method to shuffle the deck by swapping cards randomly 100 times
    public void shuffle() {
        for (int i = 0; i < 100; i++) {
            int index1 = (int) (Math.random() * 52);
            int index2 = (int) (Math.random() * 52);
            Collections.swap(cards, index1, index2);
        }
    }

    // Method to deal a card from the top of the deck
    public Card deal() {
        if (cards.isEmpty()) {
            return null; // Deck is empty, return null
        }
        return cards.remove(0); // Remove and return the top card
    }

    // Method to stack the 4 Aces on top of the deck
    public void stack() {
        ArrayList<Card> aces = new ArrayList<Card>();
        ArrayList<Card> otherCards = new ArrayList<Card>();

        // Separate Aces from other cards
        for (Card card : cards) {
            if (card.equals(new Card(14, 'c')) || card.equals(new Card(14, 'd')) ||
                    card.equals(new Card(14, 'h')) || card.equals(new Card(14, 's'))) {
                aces.add(card);
            } else {
                otherCards.add(card);
            }
        }

        // Clear the deck and add Aces first, then other cards
        cards.clear();
        cards.addAll(aces);
        cards.addAll(otherCards);
    }

    // Override toString method to provide a string representation of the deck
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Deck: [");
        for (int i = 0; i < cards.size(); i++) {
            sb.append(cards.get(i));
            if (i < cards.size() - 1) {
                sb.append(", ");
            }
        }
        sb.append("]");
        return sb.toString();
    }
}

