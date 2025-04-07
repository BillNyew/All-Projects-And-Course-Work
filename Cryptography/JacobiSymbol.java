public class JacobiSymbol {
    public static int jacobi(int a, int m) {
        if (m <= 0 || m % 2 == 0) {
            throw new IllegalArgumentException("m must be a positive odd number");
        }
        a = a % m;
        int result = 1;
        
        while (a != 0) {
            while (a % 2 == 0) {
                a /= 2;
                if (m % 8 == 3 || m % 8 == 5) {
                    result = -result;
                }
            }
            
            // Swap a and m
            int temp = a;
            a = m;
            m = temp;
            
            if (a % 4 == 3 && m % 4 == 3) {
                result = -result;
            }
            a = a % m;
        }
        
        return m == 1 ? result : 0;
    }

    public static void main(String[] args) {
        // Test cases
        int[][] testCases = {
            {10, 21},  // Jacobi(10, 21)
            {5, 13},   // Jacobi(5, 13)
            {2, 15},   // Jacobi(2, 15)
            {123, 321},// Jacobi(123, 321)
            {19, 45},  // Jacobi(19, 45)
            {0, 17},   // Jacobi(0, 17)
            {1, 23},   // Jacobi(1, 23)
            {3, 27},   // Jacobi(3, 27)
            {7, 19},   // Jacobi(7, 19)
            {4, 25},    // Jacobi(4, 25)
            {225, 103},
        };

        for (int[] testCase : testCases) {
            int a = testCase[0];
            int m = testCase[1];
            System.out.printf("Jacobi(%d, %d) = %d%n", a, m, jacobi(a, m));
        }
    }
}