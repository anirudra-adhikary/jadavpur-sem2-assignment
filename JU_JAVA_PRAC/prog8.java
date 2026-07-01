import java.util.Scanner;

class InvalidEmpDataException extends Exception {
    InvalidEmpDataException(String msg) {
        super(msg);
    }
}

class Emp {

    protected int id;
    protected int depCode;

    Emp(int id, int depCode)
            throws InvalidEmpDataException {

        if (depCode < 0 || depCode > 5)
            throw new InvalidEmpDataException(
                    "Department Code must be between 0 and 5");

        this.id = id;
        this.depCode = depCode;
    }

    void display() {
        System.out.println("ID: " + id);
        System.out.println("Department Code: " + depCode);
    }
}

class GradedEmp extends Emp {

    private char grade;
    private double average;

    GradedEmp(int id, int depCode, char grade)
            throws InvalidEmpDataException {

        super(id, depCode == 0 ? 0 : depCode);

        grade = Character.toUpperCase(grade);

        if (grade < 'A' || grade > 'E')
            throw new InvalidEmpDataException(
                    "Grade must be between A and E");

        this.grade = grade;
    }

    GradedEmp(int id, int depCode, double[] marks)
            throws InvalidEmpDataException {

        super(id, depCode == 0 ? 0 : depCode);

        double sum = 0;

        for (double m : marks) {

            if (m < 0 || m > 100)
                throw new InvalidEmpDataException(
                        "Marks must be between 0 and 100");

            sum += m;
        }

        average = sum / marks.length;
        grade = calculateGrade(average);
    }

    private char calculateGrade(double avg) {

        if (avg >= 90)
            return 'A';
        else if (avg >= 80)
            return 'B';
        else if (avg >= 70)
            return 'C';
        else if (avg >= 60)
            return 'D';
        else
            return 'E';
    }

    @Override
    void display() {

        super.display();

        if (average > 0)
            System.out.printf("Average Marks: %.2f%n",
                    average);

        System.out.println("Grade: " + grade);
    }
}

public class prog8 {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        try {

            System.out.print("Enter ID: ");
            int id = sc.nextInt();

            System.out.print(
                    "Enter Department Code (0-5): ");
            int depCode = sc.nextInt();

            GradedEmp emp;

            System.out.println("\n1. Enter Grade");
            System.out.println(
                    "2. Calculate Grade from Skill Tests");

            System.out.print("Choice: ");
            int choice = sc.nextInt();

            if (choice == 1) {

                System.out.print(
                        "Enter Grade (A-E): ");

                char grade = sc.next().charAt(0);

                emp = new GradedEmp(
                        id, depCode, grade);
            }
            else if (choice == 2) {

                try {

                    System.out.print(
                            "Number of Skill Tests: ");

                    int n = sc.nextInt();

                    if (n == 0)
                        throw new InvalidEmpDataException(
                                "No skill tests available");

                    double[] marks =
                            new double[n];

                    for (int i = 0; i < n; i++) {

                        System.out.print(
                                "Marks " + (i + 1)
                                        + ": ");

                        marks[i] =
                                sc.nextDouble();
                    }

                    emp = new GradedEmp(
                            id, depCode, marks);
                }
                catch (InvalidEmpDataException e) {

                    System.out.println(
                            "\n" + e.getMessage());

                    System.out.println(
                            "Switching to Manual Grade Entry");

                    System.out.print(
                            "Enter Grade (A-E): ");

                    char grade =
                            sc.next().charAt(0);

                    emp = new GradedEmp(
                            id, depCode, grade);
                }
            }
            else {
                throw new InvalidEmpDataException(
                        "Invalid Choice");
            }

            System.out.println(
                    "\nEmployee Details");
            emp.display();
        }
        catch (Exception e) {
            System.out.println(
                    "Error: " + e.getMessage());
        }

        sc.close();
    }
}