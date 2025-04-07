import java.util.*;

public class VigenereCipherDecrypter2 {
    private static final double[] ENGLISH_LETTER_FREQUENCIES = {
            0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
            0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
            0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074
    };

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the ciphertext: ");
        String ciphertext = scanner.nextLine();

        List<Integer> distances = new ArrayList<>();
        int keyLength = estimateKeyLengthUsingFriedman(ciphertext, true);

        decryptVigenere(ciphertext, keyLength, distances);

        scanner.close();

      
        for (int distance : distances) {
            System.out.println(distance);
        }

        // Check the mutual indices of coincidence to indicate correctness
        double avgIC = distances.stream().mapToDouble(Integer::doubleValue).average().orElse(0);
        double stdDevIC = Math.sqrt(distances.stream().mapToDouble(d -> Math.pow(d - avgIC, 2)).average().orElse(0));

        boolean isLikelyCorrect = avgIC > 0.05 && avgIC < 0.08 && stdDevIC < 0.02; // Adjust thresholds as needed

        // Output the indication
        System.out.println("\nLikely correctness of decryption: " + (isLikelyCorrect ? "UNLIKELY" : "LIKELY"));
    }

    public static void decryptVigenere(String ciphertext, int keyLength, List<Integer> distances) {
        // Remove non-alphabetic characters and convert to uppercase
        String cleanedText = ciphertext.replaceAll("[^a-zA-Z]", "").toUpperCase();

        // Divide the ciphertext into groups based on the key length
        List<StringBuilder> groupedText = new ArrayList<>();
        for (int i = 0; i < keyLength; i++) {
            groupedText.add(new StringBuilder());
        }

        for (int i = 0; i < cleanedText.length(); i++) {
            int groupIndex = i % keyLength;
            groupedText.get(groupIndex).append(cleanedText.charAt(i));
        }

        // Determine the key by decrypting each group with Caesar cipher analysis
        StringBuilder keyBuilder = new StringBuilder();
        for (StringBuilder group : groupedText) {
            int keyShift = findKeyShift(group.toString());
            char keyChar = (char) ((26 - keyShift) % 26 + 'A');
            keyBuilder.append(keyChar);
        }

        String key = keyBuilder.toString();

        // Decrypt the ciphertext using the determined key
        StringBuilder plaintextBuilder = new StringBuilder();
        for (int i = 0; i < cleanedText.length(); i++) {
            char c = cleanedText.charAt(i);
            char keyChar = key.charAt(i % keyLength);
            char decryptedChar = decryptChar(c, keyChar);
            plaintextBuilder.append(decryptedChar);
        }

        String plaintext = plaintextBuilder.toString();
        System.out.println("\nCiphertext: " + ciphertext);
        System.out.println("Key: " + key);
        System.out.println("Plaintext: " + plaintext);
    }

    private static int estimateKeyLengthUsingFriedman(String text, boolean verbose) {
        final double expectedIC = 0.068;
        double diff = Double.MAX_VALUE;
        int estimatedKeyLength = 1;

        Map<Integer, Double> keyLengthICs = new HashMap<>();

        for (int keyLength = 1; keyLength <= 20 && keyLength < text.length(); keyLength++) {
            double averageIC = calculateAverageIC(text, keyLength);
            keyLengthICs.put(keyLength, averageIC);

            if (Math.abs(averageIC - expectedIC) < diff) {
                diff = Math.abs(averageIC - expectedIC);
                estimatedKeyLength = keyLength;
            }
        }

        if (verbose) {
            System.out.println("Indices of Coincidence for different key lengths:");
            keyLengthICs.forEach((k, v) -> System.out.println("Key Length: " + k + ", IC: " + v));
        }

        return estimatedKeyLength;
    }

    private static double calculateAverageIC(String text, int keyLength) {
        List<String> groups = new ArrayList<>();
        for (int i = 0; i < keyLength; i++) {
            StringBuilder group = new StringBuilder();
            for (int j = i; j < text.length(); j += keyLength) {
                group.append(text.charAt(j));
            }
            groups.add(group.toString());
        }

        double totalIC = 0;
        for (String group : groups) {
            totalIC += calculateIC(group);
        }

        return totalIC / keyLength;
    }

    private static double calculateIC(String text) {
        int[] frequencies = new int[26];
        for (char c : text.toCharArray()) {
            frequencies[c - 'A']++;
        }

        double ic = 0;
        int n = text.length();
        for (int f : frequencies) {
            ic += (double) (f * (f - 1)) / (n * (n - 1));
        }

        return ic;
    }

    private static int findKeyShift(String group) {
        double[] frequencies = new double[26];
        for (char c : group.toCharArray()) {
            frequencies[c - 'A']++;
        }

        int n = group.length();
        for (int i = 0; i < 26; i++) {
            frequencies[i] /= n;
        }

        double maxIC = 0;
        int keyShift = 0;
        for (int shift = 0; shift < 26; shift++) {
            double ic = 0;
            for (int i = 0; i < 26; i++) {
                ic += frequencies[i] * ENGLISH_LETTER_FREQUENCIES[(i + shift) % 26];
            }
            if (ic > maxIC) {
                maxIC = ic;
                keyShift = shift;
            }
        }

        return keyShift;
    }

    private static char decryptChar(char c, char keyChar) {
        int shift = keyChar - 'A';
        char decryptedChar = (char) ((c - shift - 'A' + 26) % 26 + 'A');
        return decryptedChar;
    }
}