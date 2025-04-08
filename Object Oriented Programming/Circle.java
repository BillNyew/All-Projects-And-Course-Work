package class2_2;


public class Circle extends Shape {
    private double radius;

    public Circle(String name, double radius) {
        super(name); // Call the base class constructor to set the name
        if (radius <= 0) {
            throw new IllegalArgumentException("Radius must be greater than zero");
        }
        this.radius = radius;
    }

    public Circle(Circle otherCircle) {
        super(otherCircle); // Call the base class copy constructor to copy the name
        this.radius = otherCircle.radius;
    }

    @Override
    public String toString() {
        return String.format("Circle: Name = %s, Radius = %.2f", getName(), radius);
    }

    public double getRadius() {
        return radius;
    }
}