package RSAProject;

import java.math.BigInteger;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class RSAEncryptionPart2 {
    private static final int BLOCK_SIZE = 214;
    private static final int CERTAINTY = 40; // For the prime test (e.g., Miller-Rabin)
    private static final int BIT_LENGTH = 2048;
    private static final SecureRandom random = new SecureRandom();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("Select an option:");
            System.out.println("1 to Generate keys");
            System.out.println("2 to Encrypt message");
            System.out.println("3 to Decrypt message");
            System.out.println("4 to Exit");
            System.out.print("Input a number from 1-4: ");
            String choiceStr = scanner.nextLine();
            int choice;
            try {
                choice = Integer.parseInt(choiceStr);
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please input a number from 1-4.");
                continue;
            }

            switch (choice) {
                case 1:
                    generateKeys();
                    break;
                case 2:
                    System.out.println("Enter the path to the public key file:");
                    String publicKeyFile = scanner.nextLine();
                    System.out.println("Enter the path to the plaintext file:");
                    String plaintextFile = scanner.nextLine();
                    System.out.println("Enter the path to save the encrypted file:");
                    String encryptedFile = scanner.nextLine();
                    encryptMessage(publicKeyFile, plaintextFile, encryptedFile);
                    break;
                case 3:
                    System.out.println("Enter the path to the private key file:");
                    String privateKeyFile = scanner.nextLine();
                    System.out.println("Enter the path to the encrypted file:");
                    String encryptedMessageFile = scanner.nextLine();
                    System.out.println("Enter the path to save the plaintext file:");
                    String decryptedFile = scanner.nextLine();
                    decryptMessage(privateKeyFile, encryptedMessageFile, decryptedFile);
                    break;
                case 4:
                    System.exit(0);
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private static void generateKeys() {
        int triesP = 0, triesQ = 0;
        BigInteger p, q;

        // Generate prime p
        do {
            p = new BigInteger(BIT_LENGTH / 2, random);
            triesP++;
        } while (!p.isProbablePrime(CERTAINTY));

        // Generate prime q
        do {
            q = new BigInteger(BIT_LENGTH / 2, random);
            triesQ++;
        } while (!q.isProbablePrime(CERTAINTY));

        BigInteger n = p.multiply(q);
        BigInteger phi = (p.subtract(BigInteger.ONE)).multiply(q.subtract(BigInteger.ONE));
        BigInteger e;
        do {
            e = new BigInteger(BIT_LENGTH - 1, CERTAINTY, random); // Generate a large prime for e
        } while (!e.gcd(phi).equals(BigInteger.ONE));

        BigInteger d = e.modInverse(phi);

        // Save the public key (n, e) and private key (n, d) to files
        saveKeyToFile("public.txt", n, e);
        saveKeyToFile("private.txt", n, d);

        // Print statistics
        System.out.println("NOTE 1st LINE WILL ALWAYS BE n,");
        System.out.println("2nd LINE WILL BE e OR d IN THEIR RESPECTIVE KEYS");
        System.out.println("Number of tries to find p: " + triesP);
        System.out.println("Number of tries to find q: " + triesQ);
        System.out.println("Number of iterations to verify p is prime: " + CERTAINTY);
        System.out.println("Number of iterations to verify q is prime: " + CERTAINTY);
        System.out.println("Numerical confidence p is prime: " + (1 - 1.0 / Math.pow(2, CERTAINTY)));
        System.out.println("Numerical confidence q is prime: " + (1 - 1.0 / Math.pow(2, CERTAINTY)));
    }

    private static void encryptMessage(String publicKeyFile, String plaintextFile, String encryptedFile) {
        try {
            List<String> lines = Files.readAllLines(Paths.get(plaintextFile));
            String plaintext = String.join("\n", lines);
            BigInteger[] publicKey = readKeyFromFile(publicKeyFile);

            List<BigInteger> encryptedBlocks = encrypt(plaintext, publicKey[0], publicKey[1]);
            List<String> encryptedStrings = new ArrayList<>();
            for (BigInteger block : encryptedBlocks) {
                encryptedStrings.add(block.toString());
            }

            Files.write(Paths.get(encryptedFile), encryptedStrings);
            System.out.println("Message encrypted and saved to " + encryptedFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void decryptMessage(String privateKeyFile, String encryptedFile, String decryptedFile) {
        try {
            List<String> lines = Files.readAllLines(Paths.get(encryptedFile));
            List<BigInteger> encryptedBlocks = new ArrayList<>();
            for (String line : lines) {
                encryptedBlocks.add(new BigInteger(line));
            }
            BigInteger[] privateKey = readKeyFromFile(privateKeyFile);

            String decryptedText = decrypt(encryptedBlocks, privateKey[0], privateKey[1]);
            Files.write(Paths.get(decryptedFile), decryptedText.getBytes());
            System.out.println("Message decrypted and saved to " + decryptedFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static List<BigInteger> encrypt(String plaintext, BigInteger n, BigInteger e) {
        List<BigInteger> blocks = breakIntoBlocks(plaintext);
        List<BigInteger> encryptedBlocks = new ArrayList<>();

        for (BigInteger block : blocks) {
            encryptedBlocks.add(block.modPow(e, n));
        }

        return encryptedBlocks;
    }

    private static String decrypt(List<BigInteger> encryptedBlocks, BigInteger n, BigInteger d) {
        StringBuilder decryptedText = new StringBuilder();

        for (BigInteger encryptedBlock : encryptedBlocks) {
            BigInteger decryptedBlock = encryptedBlock.modPow(d, n);
            decryptedText.append(new String(decryptedBlock.toByteArray()));
        }

        return decryptedText.toString();
    }

    private static List<BigInteger> breakIntoBlocks(String text) {
        List<BigInteger> blocks = new ArrayList<>();

        for (int i = 0; i < text.length(); i += BLOCK_SIZE) {
            int end = Math.min(text.length(), i + BLOCK_SIZE);
            String blockString = text.substring(i, end);
            BigInteger block = new BigInteger(1, blockString.getBytes());
            blocks.add(block);
        }

        return blocks;
    }

    private static void saveKeyToFile(String filename, BigInteger n, BigInteger exp) {
        try {
            List<String> lines = new ArrayList<>();
            lines.add(n.toString());
            lines.add(exp.toString());
            Files.write(Paths.get(filename), lines);
            System.out.println("Key saved to " + filename);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static BigInteger[] readKeyFromFile(String filename) {
        try {
            List<String> lines = Files.readAllLines(Paths.get(filename));
            BigInteger n = new BigInteger(lines.get(0));
            BigInteger exp = new BigInteger(lines.get(1));
            return new BigInteger[]{n, exp};
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}

