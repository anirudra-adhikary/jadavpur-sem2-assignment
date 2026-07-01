import java.util.*;


class SpecialStack extends Stack {

    @Override
    public void push(int x) {

        if(isEmpty() || x < peek())
            super.push(x);
        else
            System.out.println(
                "Cannot push " + x +
                " because it is larger than top element " +
                peek()
            );
    }
}

public class tower_of_hanoi {

    static void arrange(Stack source,
                        Stack auxiliary,
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

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        Stack source = new Stack();
        Stack auxiliary = new Stack();
        SpecialStack destination = new SpecialStack();

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();

        System.out.println("Enter elements in random order:");

        for(int i = 0; i < n; i++) {
            source.push(sc.nextInt());
        }

        System.out.println("\nOriginal Source Stack:");
        source.display();

        arrange(source, auxiliary, destination);

        System.out.println("\nFinal Destination Stack:");
        destination.display();

        sc.close();
    }
}