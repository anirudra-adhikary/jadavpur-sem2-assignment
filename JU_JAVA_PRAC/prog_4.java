import java.util.Scanner;

class SpecialStack extends Stack {

    @Override
    public void push(int x) {
        if(isEmpty() || x < peek())
            super.push(x);
        else {
            System.out.println("Cannot push " + x + " because it is larger than top element " + peek());
        }
    }
}

public class prog_4 {
    
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        SpecialStack st = new SpecialStack();
        
        int choice;

        do {

            System.out.println("\n===== SPECIAL STACK MENU =====");
            System.out.println("1. Push");
            System.out.println("2. Pop");
            System.out.println("3. Peek");
            System.out.println("4. Display Stack");
            System.out.println("5. Exit");

            System.out.print("Enter your choice: ");
            choice = sc.nextInt();

            switch(choice) {

                case 1:
                    System.out.print("Enter element to push: ");
                    int value = sc.nextInt();
                    st.push(value);
                    break;

                case 2:
                    int popped = st.pop();
                    if(popped != -1)
                        System.out.println("Popped Element: " + popped);
                    break;

                case 3:
                    int top = st.peek();
                    if(top != -1)
                        System.out.println("Top Element: " + top);
                    break;

                case 4:
                    st.display();
                    break;

                case 5:
                    System.out.println("Exiting Program...");
                    break;

                default:
                    System.out.println("Invalid Choice");
                
            } 

        } while(choice != 5);

        sc.close();
    }
}