//public class VigenereCipher {
//    public static void main(String[] args) {
//        String plaintext = "viwhmhxpsiapadtlj";
//        String key = "tryst";
//        String ciphertext = vigenereEncrypt(plaintext, key);
//        System.out.println("Ciphertext: " + ciphertext);
//    }
//
//    public static String vigenereEncrypt(String text, String key) {
//        StringBuilder encryptedText = new StringBuilder();
//        String repeatedKey = key.repeat(text.length() / key.length()) + key.substring(0, text.length() % key.length());
//        for (int i = 0; i < text.length(); i++) {
//            char c = text.charAt(i);
//            if (Character.isLetter(c)) {
//                char keyChar = repeatedKey.charAt(i);
//                int shift = Character.toLowerCase(keyChar) - 'a';
//                char encryptedChar;
//                if (Character.isLowerCase(c)) {
//                    encryptedChar = (char) ((c - 'a' + shift) % 26 + 'a');
//                } else {
//                    encryptedChar = (char) ((c - 'A' + shift) % 26 + 'A');
//                }
//                encryptedText.append(encryptedChar);
//            } else {
//                encryptedText.append(c);
//            }
//        }
//        return encryptedText.toString();
//    }
//}
//import java.util.Scanner;
//
//public class ShiftCipher {
//    public static void main(String[] args) {
//        Scanner scanner = new Scanner(System.in);
//        System.out.print("Enter the ciphertext: ");
//        String ciphertext = scanner.nextLine();
//        System.out.print("Enter the shift value (0-25): ");
//        int shift = scanner.nextInt();
//        String plaintext = decrypt(ciphertext, shift);
//        System.out.println("Decrypted text: " + plaintext);
//        scanner.close();
//    }
//
//    public static String decrypt(String ciphertext, int shift) {
//        StringBuilder plaintext = new StringBuilder();
//        for (char c : ciphertext.toCharArray()) {
//            if (Character.isLetter(c)) {
//                char base = Character.isUpperCase(c) ? 'A' : 'a';
//                int offset = c - base;
//                int shiftedOffset = (offset - shift + 26) % 26;
//                char shiftedChar = (char) (base + shiftedOffset);
//                plaintext.append(shiftedChar);
//            } else {
//                plaintext.append(c);
//            }
//        }
//        return plaintext.toString();
//    }
//}
public class CipherGuess {

    public static void main(String[] args) {
        String message1 = "MWVAYWRMJUUQIPDHNXYGAYZRVPTSAPVBJHGBHLJGWDZNVGWMTNBZIGJJPKWH\n"
        		+ "DEGDUCSAJBFLBKGCIDLHNRQLSWGIRFWUUUWTTRDINMHDXPIQBKGKAVTWJIKPFK\n"
        		+ "XMYXHQPBEVCIDLDVRKQHWMKIFUKNIXCAGBBCKIKPWUBYYRECHXNDHTTWUBZKI\n"
        		+ "CGOBODMATFMHIVCPQEMWVAYWRKQLQVYFYNJNCMYIDMOZBOPWIVYINEDUPGOM\n"
        		+ "OQGYRKBNTCIDDSSEWHOQJZEKMOMNAQIAEKTEDOFWZRTXOYSTEJPQKIRRZVKCBSBFN\n"
        		+ "PPIPFGJBAZBXBUIVHTTTKOJUEXTRGZCHWTBODEWACIDUWZKIUYIDSMJDOFURHREXPD\n"
        		+ "EBHZQVUOVHCKNFAMCIDMGFJDQCCGCIDAJNAPYSMKTGHQYZNACJGYKMETTPQMFMF\n"
        		+ "BADQLPWGWLGICWMZHZRAQWRZNPCQ";
        String message2 = "GHPPATMATIIXGLTLDXWMAXFTGBGUETVDPXYTVXXTVAHMAXKTLZHWBGMXGWXWYXSSBDLTBWGHMKBVDLGHPXTIHGLLDBEETZTBGLMLDBEETEHGXRHNFXTGRHNEEINMWHPGRHNKKHVDTGWBEEINMWHPGFRLPHKWTGWPXEEMKRMHDBEEXTVAHMAXKEBDXVBOBEBSXWIXHIEXBLMATMBM";
        // Add more ciphertext messages as needed

        double index1 = calculateIndexOfCoincidence(message1);
        double index2 = calculateIndexOfCoincidence(message2);
        // Calculate index of coincidence for additional messages

        System.out.printf("Message 1 has an index of coincidence of %.3f and is encrypted with %s.\n", index1, guessCipher(index1));
        System.out.printf("Message 2 has an index of coincidence of %.3f and is encrypted with %s.\n", index2, guessCipher(index2));
        // Print results for additional messages
    }

    public static double calculateIndexOfCoincidence(String message) {
        int[] frequency = new int[26];
        int total = 0;

        for (char c : message.toCharArray()) {
            if (Character.isLetter(c)) {
                int index = Character.toLowerCase(c) - 'a';
                frequency[index]++;
                total++;
            }
        }

        double sum = 0;
        for (int f : frequency) {
            sum += (f * (f - 1));
        }

        return sum / (total * (total - 1));
    }

    public static String guessCipher(double index) {
        if (index > 0.06) {
            return "Vigenere";
        } else {
            return "Shift";
        }
    }
    
    
    
    
    
    
    
    
    

}













//import java.util.Scanner;
//
//public class MultiplicationTableModN {
//    public static void main(String[] args) {
//        Scanner scanner = new Scanner(System.in);
//        System.out.print("Enter the value of n: ");
//        int n = scanner.nextInt();
//
//        System.out.println("Multiplication Table (mod " + n + "):");
//        System.out.print("   |");
//        for (int i = 0; i < n; i++) {
//            System.out.printf("%4d", i);
//        }
//        System.out.println();
//        for (int i = 0; i < n; i++) {
//            System.out.printf("%3d|", i);
//            for (int j = 0; j < n; j++) {
//                System.out.printf("%4d", (i * j) % n);
//            }
//            System.out.println();
//        }
//        System.out.println("\nFinding Multiplicative Inverses:");
//        for (int m = 1; m < n; m++) {
//            boolean hasInverse = false;
//            for (int k = 1; k < n; k++) {
//                if ((m * k) % n == 1) {
//                    hasInverse = true;
//                    break;
//                }
//            }
//            System.out.println("m = " + m + " has a multiplicative inverse: " + hasInverse);
//        }
//
//        scanner.close();
//    }
//}