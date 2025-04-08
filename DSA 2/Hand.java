package HW2;

import java.util.ArrayList;

public class Hand {
    private ArrayList<Card> cards;
    private int score;
    private boolean isSoft; // New instance variable to represent if the hand is soft

    public Hand() {
        cards = new ArrayList<Card>();
        score = 0;
        isSoft = false; // Initialize as a hard hand (no Ace initially)
    }

    public void addCard(Card card) {
        cards.add(card);
        updateScore(card);
    }

    private void updateScore(Card card) {
        int cardScore = card.getScore();
        if (cardScore == 11 && score + cardScore > 21) {
            // If adding an Ace as 11 would bust the hand, treat it as 1
            cardScore = 1;
        }
        score += cardScore;

        if (cardScore == 11 && score <= 11) {
            // If an Ace is present and can be counted as 11 without busting,
            // mark the hand as soft
            isSoft = true;
        } else if (cardScore == 1 && isSoft && score <= 11) {
            // If the hand was soft, but changing an Ace from 11 to 1 prevents a bust,
            // mark the hand as hard again
            isSoft = false;
        }
    }

    public int getScore() {
        return score;
    }

    public boolean isSoft() {
        return isSoft;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Hand: [");
        for (int i = 0; i < cards.size(); i++) {
            sb.append(cards.get(i));
            if (i < cards.size() - 1) {
                sb.append(", ");
            }
        }
        sb.append("]");

        // Include whether the hand is soft or hard in the output
        sb.append(isSoft ? " (Soft)" : " (Hard)");

        sb.append(" Score: " + score);
        return sb.toString();
    }


    // Comment out the removeCard method since it's not used in Blackjack
    // public void removeCard(Card card) {
    //     cards.remove(card);
    // }
}

