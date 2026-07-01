import java.util.Scanner;
import java.util.Stack;


public class prog_3 {

    static void arrange(Stack<Integer> source,
                        Stack<Integer> auxiliary,
                        SpecialStack destination) {

        while(!source.isEmpty()) {

            int temp = source.pop();

            while(!destination.isEmpty() &&
                  destination.peek() < temp) {

                auxiliary.push(destination.pop());
            }

            destination.push(temp);

            while(!auxiliary.isEmpty()) {
                destination.push(auxiliary.pop());
            }
        }
    }

    static SpecialStack merge(SpecialStack s1,
                              SpecialStack s2) {

        Stack<Integer> temp = new Stack<>();
        SpecialStack merged = new SpecialStack();

        while(!s1.isEmpty() && !s2.isEmpty()) {

            if(s1.peek() < s2.peek())
                temp.push(s1.pop());
            else
                temp.push(s2.pop());
        }

        while(!s1.isEmpty()) {
            temp.push(s1.pop());
        }

        while(!s2.isEmpty()) {
            temp.push(s2.pop());
        }

        while(!temp.isEmpty()) {
            merged.push(temp.pop());
        }

        return merged;
    }

    public static void main(String[] args) {

        final int MAX_SIZE = 1000;

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter size of Stack 1: ");
        int n1 = sc.nextInt();

        System.out.print("Enter size of Stack 2: ");
        int n2 = sc.nextInt();

        if(n1 + n2 > MAX_SIZE) {

            System.out.println(
                "Stack Overflow: Merged stack size exceeds "
                + MAX_SIZE
            );

            sc.close();
            return;
        }

        Stack<Integer> source1 = new Stack<>();
        Stack<Integer> source2 = new Stack<>();

        Stack<Integer> auxiliary1 = new Stack<>();
        Stack<Integer> auxiliary2 = new Stack<>();

        SpecialStack s1 = new SpecialStack();
        SpecialStack s2 = new SpecialStack();

        System.out.println(
            "\nEnter elements for Stack 1 in any order:"
        );

        for(int i = 0; i < n1; i++) {
            source1.push(sc.nextInt());
        }

        System.out.println(
            "\nEnter elements for Stack 2 in any order:"
        );

        for(int i = 0; i < n2; i++) {
            source2.push(sc.nextInt());
        }

        arrange(source1, auxiliary1, s1);
        arrange(source2, auxiliary2, s2);

        System.out.println("\nSpecial Stack 1:");
        s1.display();

        System.out.println("\nSpecial Stack 2:");
        s2.display();

        SpecialStack merged = merge(s1, s2);

        System.out.println("\nMerged Stack:");
        merged.display();

        sc.close();
    }
}