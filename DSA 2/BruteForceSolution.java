package HW5;

class Point {
    double x, y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public static double distance(Point p1, Point p2) {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        return Math.sqrt(dx * dx + dy * dy);
    }
}

public class BruteForceSolution {

    public static double closestPair(Point[] points) {
        int n = points.length;
        double minDistance = Double.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double distance = Point.distance(points[i], points[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                }
            }
        }
        return minDistance;
    }

    public static void main(String[] args) {
        Point[] points = { new Point(0, 0), new Point(1, 1), new Point(2, 2),
                           new Point(3, 3), new Point(4, 4), new Point(5, 5) };

        System.out.println("Closest pair distance (brute force): " + closestPair(points));
    }
}