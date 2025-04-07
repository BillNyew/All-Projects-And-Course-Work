import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class VigenereCipherDecrypter {

    public static void main(String[] args) {
        String ciphertext = getCipherText();
        boolean verbose = true;

        int keyLength = estimateKeyLengthUsingFriedman(ciphertext, verbose);
        String key = deriveKey(ciphertext, keyLength, verbose);
        String plaintext = decrypt(ciphertext, key);

        if (verbose) {
            System.out.println("Key Length: " + keyLength);
            System.out.println("Estimated Key: " + key);
            System.out.println("Decrypted Text: " + plaintext);
        } else {
            System.out.println(plaintext);
        }
    }

    private static String getCipherText() {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.println("Enter file path or press ENTER to input ciphertext directly:");
            String input = scanner.nextLine();
            if (input.isEmpty()) {
                System.out.println("Enter the ciphertext:");
                return scanner.nextLine().toUpperCase().replaceAll("[^A-Z]", "");
            } else {
                return new String(Files.readAllBytes(Paths.get(input))).toUpperCase().replaceAll("[^A-Z]", "");
            }
        } catch (IOException e) {
            System.out.println("Error reading input: " + e.getMessage());
            System.exit(1);
            return null;
        }
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
        double totalIC = 0;
        for (int i = 0; i < keyLength; i++) {
            StringBuilder sb = new StringBuilder();
            for (int j = i; j < text.length(); j += keyLength) {
                sb.append(text.charAt(j));
            }
            totalIC += calculateIC(sb.toString());
        }
        return totalIC / keyLength;
    }

    private static double calculateIC(String segment) {
        int[] freqs = new int[26];
        for (char c : segment.toCharArray()) {
            freqs[c - 'A']++;
        }

        double ic = 0;
        int len = segment.length();
        for (int freq : freqs) {
            ic += freq * (freq - 1);
        }
        ic /= (len * (len - 1)) / 26.0;
        return ic;
    }

    private static String deriveKey(String ciphertext, int keyLength, boolean verbose) {
        StringBuilder key = new StringBuilder();
        double[] englishFreq = {0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040,
                                0.024, 0.067, 0.075, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.023, 0.001, 0.020, 0.001};

        for (int i = 0; i < keyLength; i++) {
            StringBuilder sb = new StringBuilder();
            for (int j = i; j < ciphertext.length(); j += keyLength) {
                sb.append(ciphertext.charAt(j));
            }
            key.append((char) ('A' + findBestShift(sb.toString(), englishFreq)));
        }

        if (verbose) {
            System.out.println("Derived Key: " + key.toString());
        }

        return key.toString();
    }
    private static int findBestShift(String segment, double[] englishFreq) {
        int bestShift = 0;
        double minChiSq = Double.MAX_VALUE;

        for (int shift = 0; shift < 26; shift++) {
            int[] freqs = new int[26];
            for (int i = 0; i < segment.length(); i++) {
                int index = (segment.charAt(i) - 'A' - shift + 26) % 26;
                freqs[index]++;
            }

            double chiSq = 0.0;
            int totalLetters = segment.length();
            for (int i = 0; i < 26; i++) {
                double expected = totalLetters * englishFreq[i];
                double observed = freqs[i];
                if (expected != 0) {
                    chiSq += (observed - expected) * (observed - expected) / expected;
                }
            }

            if (chiSq < minChiSq) {
                minChiSq = chiSq;
                bestShift = shift;
            }
        }

        return bestShift;
    }
    private static String decrypt(String ciphertext, String key) {
        StringBuilder decryptedText = new StringBuilder();
        for (int i = 0; i < ciphertext.length(); i++) {
            char c = ciphertext.charAt(i);
            char keyChar = key.charAt(i % key.length());
            int decryptedChar = (c - keyChar + 26) % 26 + 'A';
            decryptedText.append((char) decryptedChar);
        }
        return decryptedText.toString();
    }
}
