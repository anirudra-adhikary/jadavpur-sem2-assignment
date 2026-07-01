package prog10;

public class prog10 {
    public static void main(String[] args) {

        Animal myDog = new Dog();
        Animal myCat = new Cat();
        Animal myCow = new Cow();

        myDog.sound();  
        myCat.sound();  
        myCow.sound(); 
    }
}