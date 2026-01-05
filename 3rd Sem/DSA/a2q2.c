#include <stdio.h>
#include <stdlib.h>

struct Node {
    int player_id;
    struct Node *next;
};

struct Node* createCircle(int n) {
    int i;
    struct Node *head = NULL;
    struct Node *tail = NULL;
    for (i = 1; i <= n; i++) {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Error: Memory allocation failed.\n");
            exit(1);
        }
        newNode->player_id = i;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    tail->next = head;
    return head;
}

void solveJosephus(int n, int k) {
    struct Node *current = createCircle(n);
    if (current == NULL)
        return;

    int i;

    if (k == 1) {
        printf("With k=1, the last person (player %d) will be the survivor.\n", n);
        struct Node* temp = current;
        for (i = 0; i < n; i++) {
            struct Node* to_free = temp;
            temp = temp->next;
            if (i < n-1) {
                 printf("Player %d has been eliminated.\n", to_free->player_id);
            }
            free(to_free);
        }
         printf("\n----------------------------------\n");
         printf("The survivor is Player %d.\n", n);
         printf("----------------------------------\n");
        return;
    }

    while (current->next != current) {
        for (i = 1; i < k - 1; i++) {
            current = current->next;
        }
        struct Node *nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        printf("Player %d has been eliminated.\n", nodeToDelete->player_id);
        free(nodeToDelete);
        current = current->next;
    }
    printf("\n----------------------------------\n");
    printf("The survivor is Player %d.\n", current->player_id);
    printf("----------------------------------\n");
    free(current);
}

int main() {
    int n, k;
    printf("--- Josephus Problem Solver ---\n");
    printf("Enter the number of players (n): ");
    scanf("%d", &n);
    printf("Enter the step count (k): ");
    scanf("%d", &k);
    if (n <= 0 || k <= 0) {
        printf("Number of players and step count must be positive.\n");
        return 1;
    }
    solveJosephus(n, k);
    return 0;
}

