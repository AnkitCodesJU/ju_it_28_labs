#include <stdio.h>
#define MAX 5

int queue[MAX], front = -1, rear = -1;

void enqueue(int x) {
    if (rear == MAX - 1) { printf("Overflow\n"); return; }
    if (front == -1) front = 0;
    queue[++rear] = x;
}

void dequeue() {
    if (front == -1 || front > rear) { printf("Underflow\n"); return; }
    printf("Deleted: %d\n", queue[front++]);
}

void display() {
    if (front == -1 || front > rear) { printf("Empty\n"); return; }
    printf("Queue: ");int i;
    for (i = front; i <= rear; i++) printf("%d ", queue[i]);
    printf("\n");
}

int main() {
    int ch, x;
    while (1) {
        printf("\n1.Enqueue 2.Dequeue 3.Display 4.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Enter value: "); scanf("%d", &x); enqueue(x); break;
            case 2: dequeue(); break;
            case 3: display(); break;
            case 4: return 0;
        }
    }
}

