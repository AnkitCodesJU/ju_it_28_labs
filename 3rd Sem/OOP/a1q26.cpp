#include <iostream>
using namespace std;

class Stack {
        int* buffer;
        int top;
        int capacity;

public:
        Stack(const int &size) : capacity(size), top(-1) {
                buffer = new int[capacity];
        }

        void push(const int &item) {
                if (top == capacity - 1) {
                        cout << "Stack Overflow. Cannot push " << item << endl;
                        return;
                }
                buffer[++top] = item;
        }

        int pop() {
                if (top == -1) {
                        cout << "Stack Underflow. Cannot pop." << endl;
                        return -1;
                }
                return buffer[top--];
        }

        void disp() const {
                if (top == -1) {
                        cout << "Stack is empty." << endl;
                        return;
                }
                cout << "Stack elements (top to bottom): ";
                for (int i = top; i >= 0; i--) {
                        cout << buffer[i] << " ";
                }
                cout << endl;
        }

        ~Stack() {
                delete[] buffer;
        }
};

int main() {
        Stack s(10);

        s.push(2);
        s.push(3);
        s.push(4);
        s.push(5);

        s.pop();

        s.disp();

        return 0;
}

