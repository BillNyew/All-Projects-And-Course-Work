public class ModuloInverse {

    public static int inverseModulo(int m, int n) {
        int a = n;
        int b = m % n;
        int x = 0;
        int y = 1;
        int x0 = 1;
        int y0 = 0;

        while (b != 0) {
            int q = a / b;
            int temp = a;
            a = b;
            b = temp % b;

            temp = x;
            x = x0 - q * x;
            x0 = temp;

            temp = y;
            y = y0 - q * y;
            y0 = temp;
        }

        if (a != 1) {
            throw new ArithmeticException("Inverse does not exist.");
        }

        if (y0 < 0) {
            y0 += n;
        }

        return y0;
    }

    public static void main(String[] args) {
        int m = 19;
        int n = 8;
        int inverse = inverseModulo(m, n);
        System.out.println("The inverse of " + m + " modulo " + n + " is: " + inverse);
    }
}