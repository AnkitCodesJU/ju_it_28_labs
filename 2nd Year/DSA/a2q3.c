#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;

void insertNode(int data, int position) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    if (position == 1) {
        newNode->next = head;
        if (head != NULL) {
            head->prev = newNode;
        }
        head = newNode;
        printf("Node inserted successfully at the beginning.\n");
        return;
    }
    struct Node *temp = head;
    int k = 1;
    while (k < position - 1 && temp != NULL) {
        temp = temp->next;
        k++;
    }
    if (temp == NULL) {
        printf("Position %d is out of bounds. Cannot insert node.\n", position);
        free(newNode);
        return;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    printf("Node inserted successfully at position %d.\n", position);
}

void deleteNode(int position) {
    if (head == NULL) {
        printf("The list is empty. Nothing to delete.\n");
        return;
    }
    struct Node *nodeToDelete = head;
    if (position == 1) {
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        printf("Node at position 1 with data %d deleted.\n", nodeToDelete->data);
        free(nodeToDelete);
        return;
    }
    int k = 1;
    while (k < position && nodeToDelete != NULL) {
        nodeToDelete = nodeToDelete->next;
        k++;
    }
    if (nodeToDelete == NULL) {
        printf("Position %d is out of bounds. Cannot delete node.\n", position);
        return;
    }
    nodeToDelete->prev->next = nodeToDelete->next;
    if (nodeToDelete->next != NULL) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    }
    printf("Node at position %d with data %d deleted.\n", position, nodeToDelete->data);
    free(nodeToDelete);
}

int countNodes() {
    int count = 0;
    struct Node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void reversePrint() {
    if (head == NULL) {
        printf("The list is empty. Nothing to print.\n");
        return;
    }
    struct Node *tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    printf("The list in reverse order is: ");
    struct Node *temp = tail;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

void reverseList() {
    if (head == NULL || head->next == NULL) {
        printf("List is empty or has only one node, no need to reverse.\n");
        return;
    }
    struct Node *temp = NULL;
    struct Node *current = head;
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL) {
        head = temp->prev;
    }
    printf("The list has been successfully reversed.\n");
}

void displayList() {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    struct Node *temp = head;
    printf("The linked list is: HEAD -> ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, data, position;
    while (1) {
        printf("\n--- Doubly Linked List Operations Menu ---\n");
        printf("1. Insert a node at a specified position\n");
        printf("2. Delete a node from a specified position\n");
        printf("3. Count the number of nodes\n");
        printf("4. Reverse print the linked list\n");
        printf("5. Reverse the linked list\n");
        printf("6. Display the linked list\n");
        printf("7. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position to insert at: ");
                scanf("%d", &position);
                insertNode(data, position);
                break;
            case 2:
                printf("Enter position of node to delete: ");
                scanf("%d", &position);
                deleteNode(position);
                break;
            case 3:
                printf("The number of nodes in the list is: %d\n", countNodes());
                break;
            case 4:
                reversePrint();
                break;
            case 5:
                reverseList();
                break;
            case 6:
                displayList();
                break;
            case 7:
                printf("Exiting program.\n");
                while(head != NULL) {
                    struct Node *temp = head;
                    head = head->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
