package class2_2;

public class Rectangle extends Shape {
    private double height;
    private double width;

    public Rectangle(String name, double height, double width) {
        super(name); // Call the base class constructor to set the name
        if (height <= 0 || width <= 0) {
            throw new IllegalArgumentException("Height and width must be greater than zero");
        }
        this.height = height;
        this.width = width;
    }

    public Rectangle(Rectangle otherRectangle) {
        super(otherRectangle); // Call the base class copy constructor to copy the name
        this.height = otherRectangle.height;
        this.width = otherRectangle.width;
    }

    @Override
    public String toString() {
        return String.format("Rectangle: Name = %s, Height = %.2f, Width = %.2f", getName(), height, width);
    }

    public double getHeight() {
        return height;
    }

    public double getWidth() {
        return width;
    }
}