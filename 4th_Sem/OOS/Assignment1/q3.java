class Overflow extends Exception {
    int capacity;

    Overflow(int cap) {
        this.capacity = cap;
    }

    void printError() {
        System.out.println("pushed more data than the capacity , " + capacity);
    }
}

class Underflow extends Exception {
    Underflow() {}
}

class Stack {
    int arr[];
    int top;
    int capacity;

    Stack(int size) {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }

    void push(int value) throws Exception {
        if (top >= capacity - 1) throw new Overflow(capacity);
        arr[++top] = value;
    }

    void pop() throws Underflow {
        if (top == -1) throw new Underflow();
        top--;
    }

    void print() {
        for (int i = top; i >= 0; i--)
            System.out.print(arr[i] + " ");
        System.out.println();
    }

    public static void main(String[] args) {
        Stack s = new Stack(5);

        try {
            s.push(10);
            s.push(20);
            s.push(30);
            s.push(15);
            s.push(9);
            s.push(100); // overflow

            s.print();

            s.pop();
            s.pop();
            s.pop();
            s.pop();
            s.pop();
            s.pop();

            s.print();
        } catch (Overflow o) {
            o.printError();
        } catch (Underflow u) {
            System.out.println("Can't pop any more element. Stack is empty");
        }catch(Exception e){
                System.out.println("Excepetion");
        }
    }
}