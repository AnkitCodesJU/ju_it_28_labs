#include <iostream>
using namespace std;

class Queue {
        int* data;
        int front, rear, capacity;
public:
        Queue(const int& size) : capacity(size), front(-1), rear(-1) {
                data = new int[capacity];
        }

        void add(const int& element) {
                if ((rear + 1) % capacity == front) {
                        cout << "Queue Overflow. Cannot add " << element << endl;
                        return;
                }
                if (front == -1) {
                        front = 0;
                }
                rear = (rear + 1) % capacity;
                data[rear] = element;
        }

        int remove() {
                if (front == -1) {
                        cout << "Queue Underflow. Cannot remove." << endl;
                        return -1;
                }
                int element = data[front];
                if (front == rear) {
                        front = rear = -1;
                } else {
                        front = (front + 1) % capacity;
                }
                return element;
        }

        void disp() const {
                if (front == -1) {
                        cout << "Queue is empty." << endl;
                        return;
                }
                cout << "Queue elements (front to rear): ";
                int i = front;
                while (true) {
                        cout << data[i] << " ";
                        if (i == rear)
                                break;
                        i = (i + 1) % capacity;
                }
                cout << endl;
        }

        ~Queue() {
                delete[] data;
        }
};

int main() {
        Queue q(10);

        q.add(2);
        q.add(3);
        q.add(4);
        q.add(5);

        q.remove();
        q.remove();

        q.disp();

        return 0;
}

