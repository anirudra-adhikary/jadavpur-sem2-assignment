package prog14_18;

import java.io.Serializable;

public class Profile implements Serializable {
    private String name;
    private int age;
    private double averageMarks;

    public Profile(String name, int age, double averageMarks) {
        this.name = name;
        this.age = age;
        this.averageMarks = averageMarks;
    }

    public String getName() {
        return name;
    }

    public double getAverageMarks() {
        return averageMarks;
    }

    @Override
    public String toString() {
        return "Name: " + name + " | Age: " + age + " | Average Marks: " + averageMarks;
    }
}