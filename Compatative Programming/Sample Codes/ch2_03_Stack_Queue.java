import java.util.*;

class ch2_03_Stack_Queue {
  public static void main(String[] args) {
    Stack<Character> s = new Stack<Character>();
    Queue<Character> q = new LinkedList<Character>(); // Queue is abstract, must be instantiated with LinkedList (special case for Java Queue)

    System.out.println(s.isEmpty()); // currently s is empty, true
    System.out.println("==================");
    s.push('a');
    s.push('b');
    s.push('c');
    // stack is LIFO, thus the content of s is currently like this:
    // c <- top
    // b
    // a
    System.out.println(s.peek()); // output 'c'
    s.pop(); // pop topmost
    System.out.println(s.peek()); // output 'b'
    System.out.println(s.empty()); // currently s is not empty, false
    System.out.println("==================");

    System.out.println(q.isEmpty()); // currently q is empty, true
    System.out.println("==================");
    while (!s.isEmpty()) { // stack s still has 2 more items
      q.offer(s.peek()); // enqueue 'b', and then 'a' (the method name in Java Queue for push/enqueue operation is 'offer')
      s.pop();
    }

    System.out.println(q.peek()); // prints 'b'
    // in Java, it is harder to see the back of the queue...
  }
}
