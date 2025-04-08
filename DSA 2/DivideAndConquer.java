package HW5;

import java.util.*;



public class DivideAndConquer {

    public static double closestPair(Point[] points) {
        Point[] sortedByX = Arrays.copyOf(points, points.length);
        Arrays.sort(sortedByX, Comparator.comparingDouble(p -> p.x));
        Point[] sortedByY = Arrays.copyOf(points, points.length);
        Arrays.sort(sortedByY, Comparator.comparingDouble(p -> p.y));

        return closestPairHelper(sortedByX, sortedByY, points.length);
    }

    private static double closestPairHelper(Point[] sortedByX, Point[] sortedByY, int n) {
        // Implementation details omitted
        return 0;
    }

    public static void main(String[] args) {
        Point[] points = { new Point(0, 0), new Point(1, 1), new Point(2, 2),
                           new Point(3, 3), new Point(4, 4), new Point(5, 5) };

        System.out.println("Closest pair distance (divide and conquer): " + closestPair(points));
    }
}