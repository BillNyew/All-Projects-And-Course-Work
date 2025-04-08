package HW2;

public class Player {
    private Hand hand;
    private int standValue;
    private boolean softStand; // Added instance variable to indicate soft stand

    public Player(int standValue, boolean softStand) {
        this.standValue = standValue;
        this.softStand = softStand;
        this.hand = new Hand();
    }

    public void play(Deck deck) {
        while (hand.getScore() < standValue) {
            Card card = deck.deal();
            if (card == null) {
                break; // No more cards in the deck
            }
            hand.addCard(card);

            // Check for soft stand condition (Ace in hand)
            if (softStand && hand.isSoft() && hand.getScore() >= 17) {
                break; // Soft stand on 17 or higher
            }
        }
    }

    public boolean isBust() {
        return hand.getScore() > 21;
    }

    public int compareScores(Player otherPlayer) {
        int thisScore = hand.getScore();
        int otherScore = otherPlayer.hand.getScore();

        if (thisScore > 21 && otherScore > 21) {
            return 0; // Both players busted
        } else if (thisScore > 21) {
            return -1; // This player busted, other player wins
        } else if (otherScore > 21) {
            return 1; // Other player busted, this player wins
        } else {
            return Integer.compare(otherScore, thisScore); // Compare scores
        }
    }

    @Override
    public String toString() {
        return "Player's Hand: " + hand.toString();
    }
}