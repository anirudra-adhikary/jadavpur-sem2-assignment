class Emp {
    int id;
    int depCode;

    Emp(int id, int depCode) {
        this.id = id;
        this.depCode = depCode;
    }

    void display() {
        System.out.println("ID = " + id);
        System.out.println("Department Code = " + depCode);
    }
}

class GradedEmp extends Emp {
    char grade;

    GradedEmp(int id, int depCode, char grade) {
        super(id, depCode);
        this.grade = grade;
    }

    void display() {
        super.display();
        System.out.println("Grade = " + grade);
    }
}

public class prog4 {
    public static void main(String[] args) {
        GradedEmp e = new GradedEmp(101, 3, 'A');
        e.display();
    }
}