package HW2;

public class BlackJackBasicTest {
    public static void main(String[] args) {
        // Create a deck and shuffle it
        Deck deck = new Deck();
        System.out.println("Initial deck:");
        System.out.println(deck); // Print the initial deck (optional)
        deck.shuffle();

        // Create a player with a stand value (e.g., 17)
        int standValue = 17;
        Player player = new Player(standValue);

        // Tell the player to play
        player.play(deck);

        // Display the result of the player's hand
        System.out.println("Player's hand:");
        System.out.println(player);

        // Check if the player is bust and display the result
        if (player.isBust()) {
            System.out.println("Player is bust!");
        } else {
            // Compare the player's score with the dealer's score (or another player's score)
            int dealerScore = 18; // Replace with the actual dealer's score
            int result = player.compareScores(new Player(dealerScore));
            if (result > 0) {
                System.out.println("Player wins!");
            } else if (result < 0) {
                System.out.println("Dealer wins!");
            } else {
                System.out.println("It's a tie!");
            }
        }
    }
}