package HW1;

public class Polynomial {

    // Naive method to compute polynomial value
    public static double naivePolynomial(double x, double[] coefficients) {
        double result = 0;

        for (int i = 0; i < coefficients.length; i++) {
            result += coefficients[i] * Math.pow(x, i);
        }

        return result;
    }

    // Horner's method to compute polynomial value
    public static double hornerPolynomial(double x, double[] coefficients) {
        double result = coefficients[coefficients.length - 1];

        for (int i = coefficients.length - 2; i >= 0; i--) {
            result = result * x + coefficients[i];
        }

        return result;
    }
}