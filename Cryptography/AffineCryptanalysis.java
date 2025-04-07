import java.util.*;

public class AffineCryptanalysis {
    // English letter frequencies (source: https://en.wikipedia.org/wiki/Letter_frequency)
    private static final Map<Character, Double> ENGLISH_LETTER_FREQUENCIES = new HashMap<>() {{
        put('E', 12.02);
        put('T', 9.10);
        put('A', 8.12);
        put('O', 7.68);
        put('I', 7.31);
        put('N', 6.95);
        put('S', 6.28);
        put('R', 6.02);
        put('H', 5.92);
        put('D', 4.32);
        put('L', 3.98);
        put('U', 2.88);
        put('C', 2.71);
        put('M', 2.61);
        put('F', 2.30);
        put('Y', 2.11);
        put('W', 2.09);
        put('G', 2.03);
        put('P', 1.82);
        put('B', 1.49);
        put('V', 1.11);
        put('K', 0.69);
        put('X', 0.17);
        put('Q', 0.11);
        put('J', 0.10);
        put('Z', 0.07);
    }};

    // Function to decrypt the affine cipher
    public static String decryptAffine(String ciphertext, int a, int b) {
        StringBuilder plaintext = new StringBuilder();
        int m = 26; // Size of the alphabet (assuming English alphabet)

        // Modular multiplicative inverse of 'a'
        int aInverse = -1;
        for (int i = 0; i < m; i++) {
            if ((a * i) % m == 1) {
                aInverse = i;
                break;
            }
        }

        // Decrypt each character
        for (char c : ciphertext.toCharArray()) {
            if (Character.isLetter(c)) {
                // Convert character to uppercase for simplicity
                char ch = Character.toUpperCase(c);

                // Apply the decryption formula: D(x) = a^-1 * (x - b) mod m
                int decryptedValue = (aInverse * (ch - 'A' - b + m)) % m;

                // Handling negative values
                if (decryptedValue < 0)
                    decryptedValue += m;

                // Convert back to character
                plaintext.append((char) (decryptedValue + 'A'));
            } else {
                // If the character is not a letter, keep it unchanged
                plaintext.append(c);
            }
        }

        return plaintext.toString();
    }

    // Function to score the potential decryption
    public static double scoreDecryption(String decryption) {
        // Convert to uppercase for simplicity
        decryption = decryption.toUpperCase();

        // Calculate the score based on the frequencies of English letters
        double score = 0.0;
        for (char c : decryption.toCharArray()) {
            if (Character.isLetter(c)) {
                score += ENGLISH_LETTER_FREQUENCIES.getOrDefault(c, 0.0);
            }
        }
        return score;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input ciphertext
        System.out.print("Enter the ciphertext: ");
        String ciphertext = scanner.nextLine();

        // Brute force decryption
        System.out.println("Brute forcing decryption...");
        String bestDecryption = "";
        double bestScore = Double.NEGATIVE_INFINITY;
        int bestA = 0;
        int bestB = 0;
        for (int a = 1; a < 26; a++) {
            for (int b = 0; b < 26; b++) {
                String decryptionAttempt = decryptAffine(ciphertext, a, b);
                double score = scoreDecryption(decryptionAttempt);
                if (score > bestScore) {
                    bestScore = score;
                    bestDecryption = decryptionAttempt;
                    bestA = a;
                    bestB = b;
                }
            }
        }

        // Print the best decryption
        System.out.println("Best decryption (a=" + bestA + ", b=" + bestB + "): " + bestDecryption);

        scanner.close();
    }
}

