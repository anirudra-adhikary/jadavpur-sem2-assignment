package prog14_18;

import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class ProfileOperations {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String fileName = "Profile.bin";

        System.out.print("Enter the number of profiles to create (#n): ");
        int n = scanner.nextInt();
        scanner.nextLine(); 

        ArrayList<Profile> profilesList = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            System.out.print("Name: ");
            String name = scanner.nextLine();
            
            System.out.print("Age: ");
            int age = scanner.nextInt();
            
            System.out.print("Average Marks: ");
            double marks = scanner.nextDouble();
            scanner.nextLine(); 

            profilesList.add(new Profile(name, age, marks));
        }

        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(fileName))) {
            oos.writeObject(profilesList);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(fileName))) {
            @SuppressWarnings("unchecked")
            ArrayList<Profile> savedProfiles = (ArrayList<Profile>) ois.readObject();
            
            if (!savedProfiles.isEmpty()) {
                Profile topScorer = savedProfiles.get(0);
                
                for (Profile p : savedProfiles) {
                    if (p.getAverageMarks() > topScorer.getAverageMarks()) {
                        topScorer = p;
                    }
                }
                
                System.out.println("\nHighest Scorer Record:");
                System.out.println(topScorer.toString());
            }

        } catch (IOException | ClassNotFoundException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }
}