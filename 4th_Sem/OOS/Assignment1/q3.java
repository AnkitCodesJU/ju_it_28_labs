import java.util.*;
class Stack {
        int arr[];
        int top;
        int capacity;

        Stack(int size) {
                capacity = size;
                arr = new int[capacity];
                top = -1;
        }

        void push(int value) {
                if (top == capacity - 1) return;
                arr[++top] = value;
        }

        void pop() {
                if (top == -1) return;
                top--;
        }

        void print() {
                for (int i = top; i >= 0; i--)
                System.out.print(arr[i] + " ");
                System.out.println();
        }

        public static void main(String[] args) {
                Stack s = new Stack(30);

                s.push(10);
                s.push(20);
                s.push(30);
                s.push(15);
                s.push(9);

                s.print();

                s.pop();
                s.pop();
                s.pop();

                s.print();
        }
}

