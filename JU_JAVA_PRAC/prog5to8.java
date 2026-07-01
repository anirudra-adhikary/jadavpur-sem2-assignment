import java.util.InputMismatchException;
import java.util.Scanner;

// ==========================================
// Question 7: Custom Exception Class
// ==========================================
class InvalidEmpDataException extends Exception {
    public InvalidEmpDataException(String message) {
        super(message);
    }
}

// ==========================================
// Question 5: Base Class
// ==========================================
class Emp {
    protected int id;
    protected int depCode;

    public Emp(int id, int depCode) throws InvalidEmpDataException {
        // Enforce base class rule: Department code must be 0-5
        if (depCode < 0 || depCode > 5) {
            throw new InvalidEmpDataException("Department Code must be between 0 and 5.");
        }
        this.id = id;
        this.depCode = depCode;
    }

    public void display() {
        System.out.println("Employee ID      : " + id);
        System.out.println("Department Code  : " + depCode);
    }
}

// ==========================================
// Question 5 & 8: Derived Class
// ==========================================
class GradedEmp extends Emp {

    private char grade;
    private double averageMarks;

    // ---------------------------------------------------------
    // Constructor 1: Manual Grade Entry (Solves Q5, Q6)
    // ---------------------------------------------------------
    public GradedEmp(int id, int depCode, char grade) throws InvalidEmpDataException {
        // Q6(a): Judicious use of super keyword
        super(id, depCode);

        // Q6(b): Change DepCode 0 -> 10 while populating derived objects
        if (this.depCode == 0) {
            this.depCode = 10;
        }

        grade = Character.toUpperCase(grade);
        if (grade < 'A' || grade > 'E') {
            throw new InvalidEmpDataException("Grade must be between A and E.");
        }

        this.grade = grade;
    }

    // ---------------------------------------------------------
    // Constructor 2: Calculated Grade (Solves Q8 Restructure)
    // ---------------------------------------------------------
    public GradedEmp(int id, int depCode, double[] marks) throws InvalidEmpDataException {
        super(id, depCode);

        // Q6(b): Change DepCode 0 -> 10
        if (this.depCode == 0) {
            this.depCode = 10;
        }

        double sum = 0;
        for (double mark : marks) {
            if (mark < 0 || mark > 100) {
                throw new InvalidEmpDataException("Marks must be between 0 and 100.");
            }
            sum += mark;
        }

        this.averageMarks = sum / marks.length;
        this.grade = calculateGrade(this.averageMarks);
    }

    private char calculateGrade(double avg) {
        if (avg >= 90) return 'A';
        if (avg >= 80) return 'B';
        if (avg >= 70) return 'C';
        if (avg >= 60) return 'D';
        return 'E';
    }

    @Override
    public void display() {
        super.display(); // Calls base class display

        if (averageMarks > 0) {
            System.out.printf("Average Marks    : %.2f%n", averageMarks);
        }
        System.out.println("Grade            : " + grade);
    }
}

// ==========================================
// Main Execution Class
// ==========================================
public class prog5to8 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("======================================================");
        System.out.println("Employee Grading System (Demonstrating Q5 to Q8)");
        System.out.println("======================================================");

        while (true) {
            try {
                System.out.print("\nEnter Employee ID: ");
                int id = sc.nextInt();

                System.out.print("Enter Department Code (0-5, enter 0 to test conversion to 10): ");
                int depCode = sc.nextInt();

                int choice;
                while (true) {
                    System.out.println("\nHow would you like to assign the grade?");
                    System.out.println("1. Enter Grade Manually (Questions 5, 6, 7)");
                    System.out.println("2. Calculate Grade from Skill Tests (Question 8)");
                    System.out.print("Enter Choice (1 or 2): ");
                    
                    choice = sc.nextInt();
                    if (choice == 1 || choice == 2) break;
                    System.out.println("Invalid Choice. Try Again.");
                }

                GradedEmp emp;

                // Option 1: Manual Grade Entry
                if (choice == 1) {
                    System.out.print("Enter Grade (A-E): ");
                    char grade = sc.next().charAt(0);
                    
                    emp = new GradedEmp(id, depCode, grade);
                } 
                // Option 2: Calculated Grade Entry
                else {
                    System.out.print("Enter Number of Skill Tests: ");
                    int n = sc.nextInt();

                    if (n <= 0) {
                        throw new InvalidEmpDataException("Number of skill tests must be greater than 0.");
                    }

                    double[] marks = new double[n];
                    for (int i = 0; i < n; i++) {
                        System.out.print("Enter Marks for Test " + (i + 1) + ": ");
                        marks[i] = sc.nextDouble();
                        if (marks[i] < 0 || marks[i] > 100) {
                            throw new InvalidEmpDataException("Marks must be between 0 and 100.");
                        }
                    }
                    
                    emp = new GradedEmp(id, depCode, marks);
                }

                System.out.println("\n--- Final Employee Details ---");
                emp.display();
                break; // Exit the main loop upon successful creation and display

            } catch (InvalidEmpDataException e) {
                System.out.println("\n[Data Error] " + e.getMessage());
                System.out.println("Please enter valid data again.");
                // sc.nextLine() is sometimes needed here if the custom error happened mid-read, 
                // but usually the specific data throws it. 

            } catch (InputMismatchException e) {
                System.out.println("\n[Input Error] You entered text where a number was expected.");
                System.out.println("Please try again from the beginning.");
                sc.nextLine(); // CRITICAL: Clears the bad input from the scanner buffer
            }
        }
        
        sc.close();
    }
}