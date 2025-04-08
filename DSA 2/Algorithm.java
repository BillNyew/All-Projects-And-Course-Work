package HW1;

public class Algorithm {

    // Brute Force - Recursive
    public static double BruteForceRecursive(double x, int n) {
        if (n == 0) {
            return 1;
        } else {
            return x * BruteForceRecursive(x, n - 1);
        }
    }

    // Brute Force - Iterative
    public static double BruteForceIterative(double x, int n) {
        double result = 1;
        for (int i = 0; i < n; i++) {
            result *= x;
        }
        return result;
    }

    // Decrease and Conquer - Recursive
    public static double DecreaseConquerRecursive(double x, int n) {
        if (n == 0) {
            return 1;
        } else if (n % 2 == 0) {
            double temp = DecreaseConquerRecursive(x, n / 2);
            return temp * temp;
        } else {
            return x * DecreaseConquerRecursive(x, n - 1);
        }
    }

    // Decrease and Conquer - Iterative
    public static double DecreaseConquerIterative(double x, int n) {
        double result = 1;

        while (n > 0) {
            if (n % 2 == 1) {
                result *= x;
            }
            x *= x;
            n /= 2;
        }

        return result;
    }
}


