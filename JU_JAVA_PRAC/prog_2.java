import java.util.Scanner;

class Stack {
    private int[] arr;
    private int top;

    Stack() {
        arr = new int[2];
        top = -1;
    }

    private void resize() {
        int[] temp = new int[arr.length * 2];

        for(int i = 0; i < arr.length; i++) {
            temp[i] = arr[i];
        }

        arr = temp;
    }

    void push(int x) {

        if(top == arr.length - 1) {
            resize();
        }

        arr[++top] = x;
    }

    int pop() {

        if(top == -1) {
            System.out.println("Stack Underflow");
            return -1;
        }

        return arr[top--];
    }

    int peek() {

        if(top == -1) {
            System.out.println("Stack is Empty");
            return -1;
        }

        return arr[top];
    }

    boolean isEmpty() {
        return top == -1;
    }

    
    void display() {

        if(top == -1) {
            System.out.println("Stack is Empty");
            return;
        }

        for(int i = top; i >= 0; i--) {
            System.out.print(arr[i] + " ");
        }

        System.out.println();
    }

    void display(int depth) {

        if(depth < 0 || depth > top) {
            System.out.println("Invalid Depth");
            return;
        }

        System.out.println(arr[top - depth]);
    }
}

public class prog_2 {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        Stack st = new Stack();

        int choice;

        do {

            System.out.println("\n===== STACK MENU =====");
            System.out.println("1. Push");
            System.out.println("2. Pop");
            System.out.println("3. Peek");
            System.out.println("4. Display Stack");
            System.out.println("5. Display Element at Depth");
            System.out.println("6. Exit");

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

                    if(popped != -1) {
                        System.out.println("Popped Element: " + popped);
                    }

                    break;

                case 3:

                    int top = st.peek();

                    if(top != -1) {
                        System.out.println("Top Element: " + top);
                    }

                    break;

                case 4:

                    st.display();

                    break;

                case 5:

                    System.out.print("Enter depth: ");
                    int depth = sc.nextInt();

                    st.display(depth);

                    break;

                case 6:

                    System.out.println("Exiting Program...");
                    break;

                default:

                    System.out.println("Invalid Choice");
            }

        } while(choice != 6);

        sc.close();
    }
}