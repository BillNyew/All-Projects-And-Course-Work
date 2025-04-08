package HW5;
import java.util.Random;

public class ClosestPairRuntimeComparison {

    public static void main(String[] args) {
        Point[] points = generateRandomPoints(1000);
        
        long startTime = System.currentTimeMillis();
        double bruteForceDistance = BruteForceSolution.closestPair(points);
        long bruteForceTime = System.currentTimeMillis() - startTime;
        
        startTime = System.currentTimeMillis();
        double divideAndConquerDistance = DivideAndConquer.closestPair(points);
        long divideAndConquerTime = System.currentTimeMillis() - startTime;

        System.out.println("Brute Force - Closest pair distance: " + bruteForceDistance + ", Time: " + bruteForceTime + "ms");
        System.out.println("Divide and Conquer - Closest pair distance: " + divideAndConquerDistance + ", Time: " + divideAndConquerTime + "ms");
    }

    private static Point[] generateRandomPoints(int n) {
        Random random = new Random();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            points[i] = new Point(random.nextDouble(), random.nextDouble());
        }
        return points;
    }
}
