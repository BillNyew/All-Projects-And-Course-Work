package HW1;

public class ExecutionTimeEvaluatorAlgorithm {

    public static void main(String[] args) {
        int numberOfTrials = 1000;

        System.out.println("N Brute Force Decrease and Conquer");

        for (int n = 500; n <= 1500; n += 500) {
            double x = 900; // Replace with your desired value of x

            // Measure Brute Force
            double bruteForceTime = measureExecutionTime(x, n, numberOfTrials, true);

            // Measure Decrease and Conquer
            double decreaseConquerTime = measureExecutionTime(x, n, numberOfTrials, false);

            // Print the results
            System.out.println(n + " " + bruteForceTime + " " + decreaseConquerTime);
        }
    }

    public static double measureExecutionTime(double x, int n, int numberOfTrials, boolean useBruteForce) {
        long startTime, endTime;

        if (useBruteForce) {
            startTime = System.currentTimeMillis();
            for (int i = 0; i < numberOfTrials; i++) {
                Algorithm.BruteForceIterative(x, n);
            }
            endTime = System.currentTimeMillis();
            return (endTime - startTime) / (double) numberOfTrials;
        } else {
            startTime = System.currentTimeMillis();
            for (int i = 0; i < numberOfTrials; i++) {
                Algorithm.DecreaseConquerIterative(x, n);
            }
            endTime = System.currentTimeMillis();
            return (endTime - startTime) / (double) numberOfTrials;
        }
    }
}