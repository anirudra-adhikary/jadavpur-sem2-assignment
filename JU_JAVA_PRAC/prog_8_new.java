import java.util.Scanner;

class InvalidEmployeeDataException extends Exception {
    public InvalidEmployeeDataException(String message) {
        super(message);
    }
}

class Emp {
    protected String id;
    protected int depCode;

    public Emp(String id, int depCode) throws InvalidEmployeeDataException {
        if (depCode < 0 || depCode > 10) {
            throw new InvalidEmployeeDataException("Invalid Department Code. Must be between 0 and 10.");
        }
        this.id = id;
        this.depCode = depCode;
    }

    public void display() {
        System.out.println("\n--- Employee Details ---");
        System.out.println("ID: " + id);
        System.out.println("Department Code: " + depCode);
    }
}

class Graded_Emp extends Emp {
    private char grade;

    public Graded_Emp(String id, int depCode, char manualGrade) throws InvalidEmployeeDataException {
        super(id, depCode);
        
        if (manualGrade == 'A' || manualGrade == 'B' || manualGrade == 'a' || manualGrade == 'b') {
            throw new InvalidEmployeeDataException("Manual grade entry cannot be 'A' or 'B'.");
        }
        
        manualGrade = Character.toUpperCase(manualGrade);
        if (manualGrade < 'C' || manualGrade > 'E') {
            throw new InvalidEmployeeDataException("Invalid manual grade. Must be C, D, or E.");
        }
        
        this.grade = manualGrade;
    }

    public Graded_Emp(String id, int depCode, double[] marks) throws InvalidEmployeeDataException {
        super(id, depCode);
        this.grade = computeGrade(marks);
    }

    private char computeGrade(double[] marks) {
        double sum = 0;
        for (double mark : marks) {
            sum += mark;
        }
        double avg = sum / marks.length;

        if (avg >= 80) return 'A';
        else if (avg >= 60) return 'B';
        else if (avg >= 40) return 'C';
        else if (avg >= 20) return 'D';
        else return 'E';
    }

    @Override
    public void display() {
        super.display();
        System.out.println("Grade: " + grade);
    }
}

public class prog_8_new {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        try {
            System.out.print("Enter Employee ID: ");
            String id = scanner.nextLine();

            System.out.print("Enter Department Code (0-10): ");
            int depCode = scanner.nextInt();

            if (depCode < 0 || depCode > 10) {
                 throw new InvalidEmployeeDataException("Department Code must be between 0 and 10.");
            }

            if (depCode >= 0 && depCode <= 5) {
                System.out.println("Dep code is 0-5. No grade required.");
                Emp employee = new Emp(id, depCode);
                employee.display();
            } else {
                System.out.print("Enter number of skill tests taken: ");
                int numTests = scanner.nextInt();

                if (numTests < 0) {
                    throw new InvalidEmployeeDataException("Number of skill tests cannot be negative.");
                }

                if (numTests == 0) {
                    System.out.print("Enter grade manually (C, D, or E only): ");
                    char manualGrade = scanner.next().charAt(0);
                    
                    Graded_Emp gradedEmployee = new Graded_Emp(id, depCode, manualGrade);
                    gradedEmployee.display();
                    
                } else {
                    double[] marks = new double[numTests];
                    System.out.println("Enter marks for " + numTests + " skill tests:");
                    for (int i = 0; i < numTests; i++) {
                        System.out.print("Test " + (i + 1) + ": ");
                        marks[i] = scanner.nextDouble();
                    }
                    
                    Graded_Emp gradedEmployee = new Graded_Emp(id, depCode, marks);
                    gradedEmployee.display();
                }
            }

        } catch (InvalidEmployeeDataException e) {
            System.err.println("\nEXCEPTION CAUGHT: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("\nEXCEPTION CAUGHT: Invalid input format.");
        } finally {
            scanner.close();
        }
    }
}