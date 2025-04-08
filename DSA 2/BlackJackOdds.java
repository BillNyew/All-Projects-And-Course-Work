package HW2;


public class BlackJackOdds {
    public static void main(String[] args) {
        int simulations = 5000;
        int[] standingValues = { 16, 17, 18 };
        boolean[] standTypes = { true, false }; // true for soft stand, false for hard stand
        
        for (int dealerStand : standingValues) {
            for (boolean dealerSoftStand : standTypes) {
                for (int playerStand : standingValues) {
                    for (boolean playerSoftStand : standTypes) {
                        int dealerWins = 0;
                        int playerWins = 0;
                        int ties = 0;

                        for (int i = 0; i < simulations; i++) {
                            Player dealer = new Player(dealerStand, dealerSoftStand);
                            Player player = new Player(playerStand, playerSoftStand);
                            Deck deck = new Deck();
                            deck.shuffle();

                            // Player plays
                            player.play(deck);

                            // If the player busts, dealer wins
                            if (player.isBust()) {
                                dealerWins++;
                            } else {
                                // Dealer plays
                                dealer.play(deck);

                                // Determine the winner based on scores
                                int result = player.compareScores(dealer);
                                if (result > 0) {
                                    playerWins++;
                                } else if (result < 0) {
                                    dealerWins++;
                                } else {
                                    ties++;
                                }
                            }
                        }

                        String dealerStandType = dealerSoftStand ? "soft" : "hard";
                        String playerStandType = playerSoftStand ? "soft" : "hard";
                        double dealerWinPercentage = (double) dealerWins / simulations * 100;
                        double playerWinPercentage = (double) playerWins / simulations * 100;
                        double tiePercentage = (double) ties / simulations * 100;

                        System.out.println("dealer " + dealerStand + "(" + dealerStandType + ") vs player " + playerStand + "(" + playerStandType + "):");
                        System.out.println("Dealer won: " + dealerWinPercentage);
                        System.out.println("Player won: " + playerWinPercentage);
                        System.out.println("No winner: " + tiePercentage);
                        System.out.println();
                    }
                }
            }
        }
    }
}