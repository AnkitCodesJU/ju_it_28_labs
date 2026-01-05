#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Queue{
    int arr[MAX_SIZE];
    int front;
    int rear;
} Queue;

void init(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return q->rear == MAX_SIZE - 1;
}

void enqueue(Queue *q, int data) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) {  // Initialize queue when the first element is added
        q->front = 0;
    }
    q->arr[++q->rear] = data;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        exit(1);  // Exit if the queue is empty
    }
    int temp = q->arr[q->front];
    if (q->front == q->rear) {  // Reset queue after dequeuing the last element
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return temp;
}

int check(Queue *q) {
    if (isEmpty(q)) {
        return 0;  // Queue is empty
    } else {
        return q->rear - q->front + 1;  // Calculate the number of elements in the queue
    }
}

int main() {
    int ch, data;
    Queue q;

    while (1) {
        printf("\n1. Initialise Queue\n2. Enqueue\n3. Dequeue\n4. Check number of elements\n5. Exit\nChoice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                init(&q);
                printf("Queue initialized.\n");
                break;
            case 2:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                enqueue(&q, data);
                break;
            case 3:
                printf("Dequeued element: %d\n", dequeue(&q));
                break;
            case 4:
                printf("Number of elements in queue: %d\n", check(&q));
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

