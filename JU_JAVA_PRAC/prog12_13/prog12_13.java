package prog12_13;

import java.util.Scanner;

public class prog12_13 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("=== Setup ResizableTray ===");
        System.out.print("Enter Tray Width: ");
        int trayWidth = scanner.nextInt();
        
        System.out.print("Enter Tray Length: ");
        int trayLength = scanner.nextInt();
        
        System.out.print("Enter Plate Width: ");
        int plateWidth = scanner.nextInt();
        
        System.out.print("Enter Plate Length: ");
        int plateLength = scanner.nextInt();

        Tray tray = new Tray();
        tray.W(trayWidth);
        tray.L(trayLength);
        tray.setPlateSize(plateWidth, plateLength);
        
        System.out.println("\n--- Tray Results ---");
        tray.display();

        System.out.println("\n===========================\n");

        System.out.println("=== Setup ResizableBox ===");
        System.out.print("Enter Box Width: ");
        int boxWidth = scanner.nextInt();
        
        System.out.print("Enter Box Length: ");
        int boxLength = scanner.nextInt();
        
        System.out.print("Enter Box Depth: ");
        int boxDepth = scanner.nextInt();
        
        System.out.print("Enter Ball/Block Width: ");
        int ballWidth = scanner.nextInt();
        
        System.out.print("Enter Ball/Block Length: ");
        int ballLength = scanner.nextInt();
        
        System.out.print("Enter Ball/Block Depth: ");
        int ballDepth = scanner.nextInt();

        NewBox box = new NewBox(boxWidth, boxLength, boxDepth);
        box.setBallSize(ballWidth, ballLength, ballDepth);
        
        System.out.println("\n--- Box Results ---");
        box.display();

        scanner.close();
    }
}