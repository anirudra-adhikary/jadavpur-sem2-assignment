import java.util.Scanner;
import java.time.*;
import java.io.FileWriter;
import java.io.IOException;

class Age {

    String name;
    String dob;

    int birthDay, birthMonth, birthYear;

    int years, months, days;

    Age(String name, String dob) {

        this.name = name;
        this.dob = dob;

        extractor(dob);
    }

    void extractor(String dob) {

        String dd = dob.substring(0, 2);
        String mm = dob.substring(3, 5);
        String yyyy = dob.substring(6, 10);

        birthDay = Integer.parseInt(dd);
        birthMonth = Integer.parseInt(mm);
        birthYear = Integer.parseInt(yyyy);

        LocalDate birthDate =
            LocalDate.of(birthYear, birthMonth, birthDay);

        LocalDate today = LocalDate.now();

        Period p = Period.between(birthDate, today);

        years = p.getYears();
        months = p.getMonths();
        days = p.getDays();
    }

    int showAge() {
        return years;
    }

    String exactAge() {

        return years + " years, " +
               months + " months, " +
               days + " days";
    }

    String ageCategory() {

        if (years < 18)
            return "under age";

        else if (years >= 18 && years < 30)
            return "young adult";

        else if (years >= 30 && years < 45)
            return "matured adult";

        else if (years >= 45 && years < 60)
            return "middle aged";

        else if (years >= 60 && years < 75)
            return "senior citizen";

        else if (years >= 75 && years < 90)
            return "old age";

        else if (years >= 90 && years <= 100)
            return "very old";

        else
            return "centenarian";
    }
}

public class prog_1 {

    public static void main(String args[]) {

        Scanner sc = new Scanner(System.in);

        System.out.println(
            "\n\n____________________ Age Checker ____________________\n"
        );

        System.out.print("Enter your name: ");
        String name = sc.nextLine();

        String dob;

        while (true) {

            System.out.print("Enter DOB (DD-MM-YYYY): ");
            dob = sc.nextLine().trim();

            if (dobValidator(dob))
                break;

            else
                System.out.println("Invalid DOB. Enter again!");
        }

        Age obj = new Age(name, dob);

        System.out.println("\nYour name: " + name);

        System.out.println(
            "Your age: " + obj.showAge() + " years"
        );

        System.out.println(
            "Exact age: " + obj.exactAge()
        );

        System.out.println(
            "You are a " + obj.ageCategory()
        );

        System.out.println(
            "\n____________________ END OF PROGRAM ____________________"
        );

        try {

            FileWriter fw =
                new FileWriter("age_records.txt", true);

            fw.write("Name : " + name + "\n");

            fw.write("DOB  : " + dob + "\n");

            fw.write(
                "Age  : " + obj.showAge() + " years\n"
            );

            fw.write(
                "Exact Age : " + obj.exactAge() + "\n"
            );

            fw.write(
                "Category : " + obj.ageCategory() + "\n"
            );

            fw.write(
                "----------------------------------\n"
            );

            fw.close();

            System.out.println(
                "Data stored in file successfully!"
            );

        } catch (IOException e) {

            System.out.println(
                "Error while writing to file."
            );
        }

        sc.close();
    }

    static boolean dobValidator(String dob) {

        // Check length
        if (dob.length() != 10)
            return false;

        // Check '-' positions
        if (dob.charAt(2) != '-' ||
            dob.charAt(5) != '-')

            return false;

        // Extract parts
        String dd = dob.substring(0, 2);
        String mm = dob.substring(3, 5);
        String yyyy = dob.substring(6, 10);

        // Numeric validation
        if (!dd.matches("\\d{2}") ||
            !mm.matches("\\d{2}") ||
            !yyyy.matches("\\d{4}")) {

            return false;
        }

        int day = Integer.parseInt(dd);
        int month = Integer.parseInt(mm);
        int year = Integer.parseInt(yyyy);

        int currentYear = Year.now().getValue();

        // Future year check
        if (year > currentYear)
            return false;

        // Month validation
        if (month < 1 || month > 12)
            return false;

        int[] daysInMonth = {

            31, 28, 31, 30,
            31, 30, 31, 31,
            30, 31, 30, 31
        };

        // Leap year check
        if ((year % 400 == 0) ||
            (year % 4 == 0 &&
             year % 100 != 0)) {

            daysInMonth[1] = 29;
        }

        // Day validation
        if (day < 1 ||
            day > daysInMonth[month - 1])

            return false;

        // Future date check
        LocalDate today = LocalDate.now();

        LocalDate enteredDate =
            LocalDate.of(year, month, day);

        if (enteredDate.isAfter(today))
            return false;

        return true;
    }
}