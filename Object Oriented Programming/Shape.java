package class2_2;

public class Shape {
    protected String name; // Protected attribute to store the name

    // Parameterized constructor
    public Shape(String name) {
        this.name = name;
    }

    // Copy constructor
    public Shape(Shape other) {
        this.name = other.name;
    }

    // Getter method for the name attribute
    public String getName() {
        return name;
    }
}