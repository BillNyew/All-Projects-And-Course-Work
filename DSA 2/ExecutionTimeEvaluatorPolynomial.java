package HW1;


public class ExecutionTimeEvaluatorPolynomial {

    public static void main(String[] args) {
        int numberOfTrials = 1000;

        System.out.println("N NaiveMethodTime HornerMethodTime");

        // Example coefficients: p(x) = 2 + 3x + 4x^2
        double[] coefficients = {2, 3, 4};

        for (int n = 500; n <= 1500; n += 500) {
            double x = 0.9; // Replace with your desired value of x

            // Measure Naive Method
            double naiveMethodTime = measureExecutionTime(x, coefficients, n, numberOfTrials, true);
            
            // Measure Horner's Method
            double hornerMethodTime = measureExecutionTime(x, coefficients, n, numberOfTrials, false);

            // Print the results
            System.out.println(n + " " + naiveMethodTime + " " + hornerMethodTime);
        }
    }

    public static double measureExecutionTime(double x, double[] coefficients, int n, int numberOfTrials, boolean useNaiveMethod) {
        long startTime, endTime;

        if (useNaiveMethod) {
            startTime = System.currentTimeMillis();
            for (int i = 0; i < numberOfTrials; i++) {
                Polynomial.naivePolynomial(x, coefficients);
            }
            endTime = System.currentTimeMillis();
        } else {
            startTime = System.currentTimeMillis();
            for (int i = 0; i < numberOfTrials; i++) {
                Polynomial.hornerPolynomial(x, coefficients);
            }
            endTime = System.currentTimeMillis();
        }

        return (endTime - startTime) / (double) numberOfTrials;
    }
}
