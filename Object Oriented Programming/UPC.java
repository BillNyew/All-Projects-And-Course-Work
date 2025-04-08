package HW1B;

// This is the starting version of the UPC-A scanner
// that needs to be filled in for the homework

// Import necessary libraries for image processing (assuming DUImage class is from an external library)
public class UPC {

    //--------------------------------------------
    // Scan in the bit pattern from the image
    // Takes the filename of the image
    // Returns an int array of the 95 scanned bits
    //--------------------------------------------
    public static int[] scanImage(String filename) {

        // Load the barcode image using the specified filename
        DUImage barCodeImage = new DUImage(filename);

        // Define constants and variables for image processing
        int imageWidth = 200;
        int imageHeight = 100;
        int startX = 5;
        int moduleWidth = 2;
        int numModules = (imageWidth - startX) / moduleWidth;

        // Create an array to store the scanned bits
        int[] scannedBits = new int[numModules];

        // Loop through each module in the image and determine if it's black or white
        for (int i = 0; i < numModules; i++) {
            int x = startX + i * moduleWidth;
            int y = imageHeight / 2;
            int red = barCodeImage.getRed(x, y);
            boolean isBlack = red == 0;
            scannedBits[i] = isBlack ? 1 : 0;
        }

        // Return the scanned bits
        return scannedBits;
    }

    //--------------------------------------------
    // Finds the matching digit for the given pattern
    // This is a helper method for decodeScan
    // Takes the full 95 scanned pattern as well as
    // a starting location in that pattern where we
    // want to look
    // Also takes in a boolean to indicate if this is a
    // left or right pattern
    // Returns an int indicating which digit matches
    // Any pattern that doesn't match anything will be -1
    //--------------------------------------------
    public static int matchPattern(int[] scanPattern, int startIndex, boolean left) {

        // Define patterns for each digit (0-9) in UPC-A barcode
        int[][] digitPat = {
            {0, 0, 0, 1, 1, 0, 1},
            {0, 0, 1, 1, 0, 0, 1},
            {0, 0, 1, 0, 0, 1, 1},
            {0, 1, 1, 1, 1, 0, 1},
            {0, 1, 0, 0, 0, 1, 1},
            {0, 1, 1, 0, 0, 0, 1},
            {0, 1, 0, 1, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1},
            {0, 1, 1, 0, 1, 1, 1},
            {0, 0, 0, 1, 0, 1, 1}
        };

        // Check if the given pattern matches any of the digit patterns
        if (left) {
            for (int i = 0; i < 10; i++) {
                boolean check = true;
                for (int j = 0; j < 7; j++) {
                    if (scanPattern[startIndex + j] != digitPat[i][j]) {
                        check = false;
                        break;
                    }
                }
                if (check) {
                    return i;
                }
            }
            return -1;
        } else {
            for (int i = 0; i < 10; i++) {
                boolean check = true;
                for (int j = 0; j < 7; j++) {
                    if (scanPattern[startIndex + j] == digitPat[i][j]) {
                        check = false;
                        break;
                    }
                }
                if (check) {
                    return i;
                }
            }
            return -1;
        }
    }

    //--------------------------------------------
    // Performs a full scan decode that turns all 95 bits
    // into 12 digits
    // Takes the full 95 bit scanned pattern
    // Returns an int array of 12 digits
    // If any digit scanned incorrectly it is returned as a -1
    // If the start, middle, or end patterns are incorrect
    // it provides an error and exits
    //--------------------------------------------
    public static int[] decodeScan(int[] scanPattern) {

        // Create an array to store the decoded barcode digits
        int[] barcode = new int[12];

        // Decode the left six digits
        for (int i = 0; i < 6; i++) {
            barcode[i] = UPC.matchPattern(scanPattern, (i * 7) + 3, true);
        }

        // Decode the right six digits
        for (int i = 6; i < 12; i++) {
            barcode[i] = UPC.matchPattern(scanPattern, (i * 7) + 8, false);
        }

        // Return the decoded barcode
        return barcode;
    }

    //--------------------------------------------
    // Do the checksum of the digits here
    // All digits are assumed to be in range 0..9
    // Returns true if check digit is correct and false otherwise
    //--------------------------------------------
    public static boolean verifyCode(int[] digits) {

        // Check if the number of digits is correct (12 digits)
        if (digits.length != 12) {
            return false;
        }

        // Calculate the checksum and verify it
        int sumEven = 0;
        int sumOdd = 0;

        // Calculate the sums of even and odd positioned digits
        for (int i = 0; i < 11; i++) {
            if (i % 2 == 0) {
                sumEven += digits[i];
            } else {
                sumOdd += digits[i];
            }
        }

        // Calculate the check digit and compare it to the last digit
        int total = (sumEven * 3) + sumOdd;
        int checkDigit = (10 - (total % 10)) % 10;
        return checkDigit == digits[11];
    }

    //--------------------------------------------
    // The main method scans the image, decodes it,
    // and then validates it
    //--------------------------------------------
    public static void main(String[] args) {
        // file name to process.
        // Note: change this to other files for testing
        String barcodeFileName = "barcodeUpsidedown.png";

        // optionally get file name from command-line args
        if (args.length == 1) {
            barcodeFileName = args[0];
        }

        // scanPattern is an array of 95 ints (0..1)
        int[] scanPattern = scanImage(barcodeFileName);

        // Display the bit pattern scanned from the image
        System.out.println("Original scan");
        for (int i = 0; i < scanPattern.length; i++) {
            System.out.print(scanPattern[i]);
        }
        System.out.println(""); // the \n

        // digits is an array of 12 ints (0..9)
        int[] digits = decodeScan(scanPattern);

        // Display the digits and check for scan errors
        boolean scanError = false;
        System.out.println("Digits");
        for (int i = 0; i < 12; i++) {
            System.out.print(digits[i] + " ");
            if (digits[i] == -1) {
                scanError = true;
            }
        }
        System.out.println("");

        // Check if there is a scan error or validate the barcode
        if (scanError) {
            System.out.println("Scan error");
        } else { // Scanned in correctly - look at checksum
            if (verifyCode(digits)) {
                System.out.println("Passed Checksum");
            } else {
                System.out.println("Failed Checksum");
            }
        }
    }
}
