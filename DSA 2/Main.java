package HW6;

import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        ShortestPath finder = new ShortestPath();
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("Enter start word:");
            String start = scanner.nextLine().trim().toLowerCase();
            System.out.println("Enter end word:");
            String end = scanner.nextLine().trim().toLowerCase();

            List<String> path = finder.findShortestPath(start, end);
            if (path.isEmpty()) {
                System.out.println("No path exists.");
            } else {
                System.out.println("Shortest path: " + path);
                System.out.println("Length of path: " + (path.size() - 1));
            }

            break;
        }
        scanner.close();
    }
}
