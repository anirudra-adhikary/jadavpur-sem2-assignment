package prog11;

import java.util.Arrays;
import java.util.Scanner;

public class prog11 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the number of elements you want to sort: ");
        int n = scanner.nextInt();
        
        int[] numbers = new int[n];
        
        System.out.println("Enter the " + n + " integers (separated by spaces or pressing Enter):");
        for (int i = 0; i < n; i++) {
            numbers[i] = scanner.nextInt();
        }
        
        System.out.println("\nOriginal array: " + Arrays.toString(numbers));
        
        Sortable sorter = new BubbleSort();
        sorter.sort(numbers);
        
        System.out.println("Sorted array:   " + Arrays.toString(numbers));
        
        scanner.close();
    }
}