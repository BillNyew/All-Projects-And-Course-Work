import java.math.BigInteger;

public class ModExp {
    public static void main(String[] args) {
        // Example values for b, e, and m
        BigInteger b = new BigInteger("123456789");
        BigInteger e = new BigInteger("987654321");
        BigInteger m = new BigInteger("1000000007");

        // Reduce b mod m
        b = b.mod(m);

        // Calculate b^e mod m
        BigInteger result = modExp(b, e, m);
        System.out.println("Result: " + result);
    }

    // Square-and-multiply algorithm for modular exponentiation
    public static BigInteger modExp(BigInteger b, BigInteger e, BigInteger m) {
        BigInteger result = BigInteger.ONE;
        while (e.compareTo(BigInteger.ZERO) > 0) {
            if (e.testBit(0)) {  // if e is odd
                result = result.multiply(b).mod(m);
            }
            b = b.multiply(b).mod(m);
            e = e.shiftRight(1);  // equivalent to e /= 2
        }
        return result;
    }
}