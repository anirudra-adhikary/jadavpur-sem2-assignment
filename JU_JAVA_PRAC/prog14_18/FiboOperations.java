package prog14_18;

import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class FiboOperations {
    public static void main(String[] args) {
        String textFileName = "Fibo.txt";
        String binFileName = "Fibo.bin";

        try (PrintWriter writer = new PrintWriter(new FileWriter(textFileName))) {
            int n1 = 0, n2 = 1;
            for (int i = 0; i < 10; ++i) {
                writer.print(n1 + " ");
                int nextTerm = n1 + n2;
                n1 = n2;
                n2 = nextTerm;
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        try {
            Scanner fileScanner = new Scanner(new File(textFileName));
            ArrayList<Integer> fibNumbers = new ArrayList<>();
            while (fileScanner.hasNextInt()) {
                fibNumbers.add(fileScanner.nextInt());
            }
            fileScanner.close();

            int last = fibNumbers.get(fibNumbers.size() - 1);
            int secondLast = fibNumbers.get(fibNumbers.size() - 2);

            try (PrintWriter appender = new PrintWriter(new FileWriter(textFileName, true))) {
                int nextTerm = last + secondLast;
                while (nextTerm < 250) {
                    appender.print(nextTerm + " ");
                    secondLast = last;
                    last = nextTerm;
                    nextTerm = last + secondLast;
                }
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        try (Scanner textReader = new Scanner(new File(textFileName));
             DataOutputStream binWriter = new DataOutputStream(new FileOutputStream(binFileName))) {
            
            while (textReader.hasNextInt()) {
                binWriter.writeInt(textReader.nextInt());
            }
            
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}