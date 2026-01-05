#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* createTree(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    int choice;
    printf("Insert to the left or right of %d? (1 = left, 2 = right): ", root->data);
    scanf("%d", &choice);

    if (choice == 1) {
        root->left = createTree(root->left, data);
    } else if (choice == 2) {
        root->right = createTree(root->right, data);
    } else {
        printf("Invalid choice. Try again.\n");
    }

    return root;
}

void inorderTraversal(struct Node* root) {
    if (root == NULL) {
    return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

void preorderTraversal(struct Node* root) {
    if (root == NULL) {
    return;
    }
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(struct Node* root) {
    if (root == NULL) {
    return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

void freeTree(struct Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node (Create Tree)\n");
        printf("2. In-Order Traversal\n");
        printf("3. Pre-Order Traversal\n");
        printf("4. Post-Order Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = createTree(root, value);
                break;
            case 2:
                if (root == NULL) {
    printf("No root.\n");
    break;
    }
                printf("In-Order Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                if (root == NULL) {
    printf("No root.\n");
    break;
    }
                printf("Pre-Order Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 4:
                if (root == NULL) {
    printf("No root.\n");
    break;
    }
                printf("Post-Order Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 5:
                freeTree(root);
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

