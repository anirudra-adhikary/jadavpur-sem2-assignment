public class prog9 {
    public static void main(String[] args) {

        Shape myRectangle = new Rectangle(5.0, 10.0);
        Shape myCircle = new Circle(3.0);
        Shape myTriangle = new Triangle(4.0, 6.0);

        System.out.println("Rectangle Area: " + myRectangle.getArea());
        System.out.println("Circle Area: " + myCircle.getArea());
        System.out.println("Triangle Area: " + myTriangle.getArea());
    }
}