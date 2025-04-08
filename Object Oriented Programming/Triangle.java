package class2_2;

public class Triangle extends Shape {
    private double lengthA;
    private double lengthB;
    private double lengthC;

    public Triangle(String name, double lengthA, double lengthB, double lengthC) {
        super(name); // Call the base class constructor to set the name
        if (lengthA <= 0 || lengthB <= 0 || lengthC <= 0) {
            throw new IllegalArgumentException("Side lengths must be greater than zero");
        }
        this.lengthA = lengthA;
        this.lengthB = lengthB;
        this.lengthC = lengthC;
    }

    public Triangle(Triangle otherTriangle) {
        super(otherTriangle); // Call the base class copy constructor to copy the name
        this.lengthA = otherTriangle.lengthA;
        this.lengthB = otherTriangle.lengthB;
        this.lengthC = otherTriangle.lengthC;
    }

    @Override
    public String toString() {
        return String.format("Triangle: Name = %s, Side A = %.2f, Side B = %.2f, Side C = %.2f",
                getName(), lengthA, lengthB, lengthC);
    }

    public double getLengthA() {
        return lengthA;
    }

    public double getLengthB() {
        return lengthB;
    }

    public double getLengthC() {
        return lengthC;
    }
}