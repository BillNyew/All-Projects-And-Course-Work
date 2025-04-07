import java.util.Scanner;
//YOU HAVE TO INPUT NUMBERS FOR A1 AN N1 SUCH AS: 5 9  AS INPUT, DON'T INCLUDE MOD
//!!!
//!!!
//!!!
//!!!
public class ChineseRemainderTheorem {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the first congruence (a1 mod n1):");
        int a1 = scanner.nextInt();
        int n1 = scanner.nextInt();

        System.out.println("Enter the second congruence (a2 mod n2):");
        int a2 = scanner.nextInt();
        int n2 = scanner.nextInt();

        int[] result = solveCongruences(a1, n1, a2, n2);
        System.out.println("Solution: x ≡ " + result[0] + " (mod " + result[1] + ")");
    }

    public static int[] solveCongruences(int a1, int n1, int a2, int n2) {
        int[] result = new int[2];
        int[] inv = new int[2];

        // Calculate inverses
        inv[0] = inverseModN(n1, n2);
        inv[1] = inverseModN(n2, n1);

        // Calculate x
        result[0] = (a1 * n2 * inv[0] + a2 * n1 * inv[1]) % (n1 * n2);

        // Calculate modulus
        result[1] = n1 * n2;

        return result;
    }

    public static int inverseModN(int a, int n) {
        int t = 0, newt = 1;
        int r = n, newr = a;

        while (newr != 0) {
            int quotient = r / newr;

            int temp = newt;
            newt = t - quotient * newt;
            t = temp;

            temp = newr;
            newr = r - quotient * newr;
            r = temp;
        }

        if (r > 1) {
            throw new IllegalArgumentException("Numbers are not coprime");
        }

        if (t < 0) {
            t += n;
        }

        return t;
    }
}