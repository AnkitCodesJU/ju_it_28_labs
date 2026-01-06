#include <stdio.h>
#include <ctype.h>

char stack[100];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }
int isEmpty() { return top == -1; }
char peek() { return stack[top]; }

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int main() {
    char infix[100];
    int i;
    printf("Enter infix expression: ");
    scanf("%s", infix);

    printf("Postfix: ");
    for (i = 0; infix[i]; i++) {
        char c = infix[i];
        if (isalnum(c)) {
            printf("%c", c); /* operand */
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (!isEmpty() && peek() != '(') printf("%c", pop());
            pop(); /* remove '(' */
        } else { /* operator */
            while (!isEmpty() && precedence(peek()) >= precedence(c))
                printf("%c", pop());
            push(c);
        }
    }
    while (!isEmpty()) printf("%c", pop());
    printf("\n");
    return 0;
}

