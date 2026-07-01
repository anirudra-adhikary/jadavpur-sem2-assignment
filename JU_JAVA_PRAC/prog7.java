class InvalidEmpDataException extends Exception {
    InvalidEmpDataException(String msg) {
        super(msg);
    }
}

class Emp {
    int id;
    int depCode;

    Emp(int id, int depCode) throws InvalidEmpDataException {
        if (depCode < 0 || depCode > 5)
            throw new InvalidEmpDataException("Invalid Department Code");

        this.id = id;
        this.depCode = depCode;
    }
}

class GradedEmp extends Emp {
    char grade;

    GradedEmp(int id, int depCode, char grade)
            throws InvalidEmpDataException {

        super(id, depCode);

        if (grade < 'A' || grade > 'E')
            throw new InvalidEmpDataException("Invalid Grade");

        this.grade = grade;
    }

    void display() {
        System.out.println("ID = " + id);
        System.out.println("Department Code = " + depCode);
        System.out.println("Grade = " + grade);
    }
}

public class prog7 {
    public static void main(String[] args) {
        try {
            GradedEmp g = new GradedEmp(104, 2, 'F');
            g.display();
        }
        catch (InvalidEmpDataException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}