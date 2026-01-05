#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void insertNode(int data, int position) {
    int k = 1;
    struct Node *newNode, *temp;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = data;
    if (position == 1) {
        newNode->next = head;
        head = newNode;
        printf("Node inserted successfully at the beginning.\n");
        return;
    }
    temp = head;
    while (temp != NULL && k < position - 1) {
        temp = temp->next;
        k++;
    }
    if (temp != NULL) {
        newNode->next = temp->next;
        temp->next = newNode;
        printf("Node inserted successfully at position %d.\n", position);
    }
    else {
        printf("Position %d is out of bounds. Cannot insert node.\n", position);
        free(newNode);
    }
}

void deleteNode(int position) {
    if (head == NULL) {
        printf("The list is empty. Nothing to delete.\n");
        return;
    }
    struct Node *temp = head, *nodeToDelete;
    if (position == 1) {
        head = head->next;
        printf("Node at position 1 with data %d deleted.\n", temp->data);
        free(temp);
        return;
    }
    int k = 1;
    while (temp != NULL && k < position - 1) {
        temp = temp->next;
        k++;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position %d is out of bounds. Cannot delete node.\n", position);
        return;
    }
    nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
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

void reversePrint(struct Node *current) {
    if (current == NULL) {
        return;
    }
    reversePrint(current->next);
    printf("%d -> ", current->data);
}

void reverseList() {
    if (head == NULL || head->next == NULL) {
        printf("List is empty or has only one node, no need to reverse.\n");
        return;
    }
    struct Node *prevNode = NULL;
    struct Node *currentNode = head;
    struct Node *nextNode = NULL;
    while (currentNode != NULL) {
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    head = prevNode;
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
        printf("\n--- Singly Linked List Operations Menu ---\n");
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
                if (head == NULL) {
                    printf("The list is empty. Nothing to print.\n");
                }
                else {
                    printf("The list in reverse order is: ");
                    reversePrint(head);
                    printf("\n");
                }
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
