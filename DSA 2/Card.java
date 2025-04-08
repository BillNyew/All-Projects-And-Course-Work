package HW2;

public class Card {
    // Private instance variables to store the rank and suit of the card
    private int rank;
    private char suit;

    // Constructor to create a new Card with the given rank and suit
    public Card(int rank, char suit) {
        this.rank = rank;
        this.suit = suit;
    }

    // Copy constructor to create a new Card as a copy of another Card
    public Card(Card other) {
        this.rank = other.rank;
        this.suit = other.suit;
    }

    // Override toString method to provide a string representation of the card
    @Override
    public String toString() {
        String rankStr;
        switch (rank) {
            case 11:
                rankStr = "J";
                break;
            case 12:
                rankStr = "Q";
                break;
            case 13:
                rankStr = "K";
                break;
            case 14:
                rankStr = "A";
                break;
            default:
                rankStr = String.valueOf(rank);
                break;
        }
        return "Card: " + rankStr + suit;
    }

    // Override equals method to compare two cards for equality
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true; // If the objects are the same reference, they are equal
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false; // If the objects are not of the same class, they are not equal
        }
        Card otherCard = (Card) obj; // Cast the object to a Card
        return rank == otherCard.rank && suit == otherCard.suit; // Cards are equal if rank and suit match
    }

    // Method to get the score of a single card based on its rank
    public int getScore() {
        if (rank >= 2 && rank <= 10) {
            return rank; // For numbered cards, the score is the same as the rank
        } else if (rank >= 11 && rank <= 13) {
            return 10; // For face cards (J, Q, K), the score is 10
        } else {
            return 11; // For Ace (A), the score is typically 11, but you can adjust it as needed
        }
    }
}