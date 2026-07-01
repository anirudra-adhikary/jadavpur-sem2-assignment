class Emp {
    int id;
    int depCode;

    Emp(int id, int depCode) {
        this.id = id;
        this.depCode = depCode;
    }
}

class GradedEmp extends Emp {
    char grade;

    GradedEmp(int id, int depCode, char grade) {
        super(id, (depCode == 0) ? 10 : depCode);
        this.grade = grade;
    }

    void display() {
        System.out.println("ID = " + id);
        System.out.println("Department Code = " + depCode);
        System.out.println("Grade = " + grade);
    }
}

public class prog6b {
    public static void main(String[] args) {
        GradedEmp g = new GradedEmp(103, 0, 'A');

        g.display();
    }
}