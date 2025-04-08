package class2_2;



	public static void main(String[] args) {
		// TODO Auto-generated method stub
		class Circle {
		    private String name;
		    private double radius;

		    public Circle(String name, double radius) {
		        if (name == null || name.isBlank() || name.strip().isEmpty()) {
		            throw new IllegalArgumentException("Name cannot be null or empty");
		        }
		        if (radius <= 0) {
		            throw new IllegalArgumentException("Radius must be greater than zero");
		        }
		        this.name = name.strip();
		        this.radius = radius;
		    }

		    public boolean equals(Object other) {
		        if (this == other) {
		            return true;
		        }
		        if (other instanceof Circle) {
		            Circle otherCircle = (Circle) other;
		            return this.name.equals(otherCircle.name) && this.radius == otherCircle.radius;
		        }
		        return false;
		    }

		    public String toString() {
		        return String.format("Circle: Name = %s, Radius = %.2f", name, radius);
		    }

		    public String getName() {
		        return name;
		    }

		    public double getRadius() {
		        return radius;
		    }
		}

		class Triangle {
		    private String name;
		    private double lengthA;
		    private double lengthB;
		    private double lengthC;

		    public Triangle(String name, double lengthA, double lengthB, double lengthC) {
		        if (name == null || name.isBlank() || name.strip().isEmpty()) {
		            throw new IllegalArgumentException("Name cannot be null or empty");
		        }
		        if (lengthA <= 0 || lengthB <= 0 || lengthC <= 0) {
		            throw new IllegalArgumentException("Side lengths must be greater than zero");
		        }
		        if (lengthA + lengthB <= lengthC || lengthA + lengthC <= lengthB || lengthB + lengthC <= lengthA) {
		            throw new IllegalArgumentException("Triangle inequality violation");
		        }
		        this.name = name.strip();
		        this.lengthA = lengthA;
		        this.lengthB = lengthB;
		        this.lengthC = lengthC;
		    }

		    public boolean equals(Object other) {
		        if (this == other) {
		            return true;
		        }
		        if (other instanceof Triangle) {
		            Triangle otherTriangle = (Triangle) other;
		            return this.name.equals(otherTriangle.name) && this.lengthA == otherTriangle.lengthA &&
		                    this.lengthB == otherTriangle.lengthB && this.lengthC == otherTriangle.lengthC;
		        }
		        return false;
		    }

		    public String toString() {
		        return String.format("Triangle: Name = %s, Side A = %.2f, Side B = %.2f, Side C = %.2f",
		                name, lengthA, lengthB, lengthC);
		    }

		    public String getName() {
		        return name;
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

		class Rectangle {
		    private String name;
		    private double height;
		    private double width;

		    public Rectangle(String name, double height, double width) {
		        if (name == null || name.isBlank() || name.strip().isEmpty()) {
		            throw new IllegalArgumentException("Name cannot be null or empty");
		        }
		        if (height <= 0 || width <= 0) {
		            throw new IllegalArgumentException("Height and width must be greater than zero");
		        }
		        this.name = name.strip();
		        this.height = height;
		        this.width = width;
		    }

		    public boolean equals(Object other) {
		        if (this == other) {
		            return true;
		        }
		        if (other instanceof Rectangle) {
		            Rectangle otherRectangle = (Rectangle) other;
		            return this.name.equals(otherRectangle.name) && this.height == otherRectangle.height &&
		                    this.width == otherRectangle.width;
		        }
		        return false;
		    }

		    public String toString() {
		        return String.format("Rectangle: Name = %s, Height = %.2f, Width = %.2f", name, height, width);
		    }

		    public String getName() {
		        return name;
		    }

		    public double getHeight() {
		        return height;
		    }

		    public double getWidth() {
		        return width;
		    }
		}

		public class ShapeTest {
		    public static void main(String[] args) {
		        // Testing the Circle class
		        try {
		            Circle circle1 = new Circle("Circle1", 5.0);
		            System.out.println(circle1.toString());

		            Circle circle2 = new Circle(circle1);
		            System.out.println(circle2.toString());
		        } catch (IllegalArgumentException e) {
		            System.out.println("Circle validation error: " + e.getMessage());
		        }

		        // Testing the Triangle class
		        try {
		            Triangle triangle1 = new Triangle("Triangle1", 3.0, 4.0, 5.0);
		            System.out.println(triangle1.toString());

		            Triangle triangle2 = new Triangle(triangle1);
		            System.out.println(triangle2.toString());
		        } catch (IllegalArgumentException e) {
		            System.out.println("Triangle validation error: " + e.getMessage());
		        }

		        // Testing the Rectangle class
		        try {
		            Rectangle rectangle1 = new Rectangle("Rectangle1", 4.0, 6.0);
		            System.out.println(rectangle1.toString());

		            Rectangle rectangle2 = new Rectangle(rectangle1);
		            System.out.println(rectangle2.toString());
		        } catch (IllegalArgumentException e) {
		            System.out.println("Rectangle validation error: " + e.getMessage());
		        }
		    }
		}
	}



