#include <stdio.h>

int s1[100], s2[100], t1 = -1, t2 = -1;

void push1(int x) { s1[++t1] = x; }
void push2(int x) { s2[++t2] = x; }
int pop1() { return s1[t1--]; }
int pop2() { return s2[t2--]; }

void enqueue(int x) { push1(x); }

int dequeue() {
    if (t1 < 0 && t2 < 0) {
        printf("Underflow\n");
        return -1;
    }
    if (t2 < 0) while (t1 >= 0) push2(pop1());
    return pop2();
}

int main() {
    int ch, x;
    while (1) {
        printf("\n1.Enqueue 2.Dequeue 3.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Enter value: "); scanf("%d", &x); enqueue(x); break;
            case 2: x = dequeue(); if (x != -1) printf("Dequeued: %d\n", x); break;
            case 3: return 0;
        }
    }
}
