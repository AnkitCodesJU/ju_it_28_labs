#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
        int data;
        struct Node* left;
        struct Node* right;
}Node;

Node* newNode(int data){
        Node* temp = (Node*)malloc(sizeof(Node*));
        temp->data = data;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
}

Node* insert(Node* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->data) node->left = insert(node->left, key);
    else if (key > node->data) node->right = insert(node->right, key);
    return node;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->data == key) return root;
    if (root->data < key) return search(root->right, key);
    return search(root->left, key);
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current != NULL && current->left != NULL) current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void findPreSuc(Node* root, Node** pre, Node** suc, int key) {
    if (root == NULL) return;
    if (root->data == key) {
        if (root->left != NULL) {
            Node* tmp = root->left;
            while (tmp->right) tmp = tmp->right;
            *pre = tmp;
        }
        if (root->right != NULL) {
            Node* tmp = root->right;
            while (tmp->left) tmp = tmp->left;
            *suc = tmp;
        }
        return;
    }
    if (root->data > key) {
        *suc = root;
        findPreSuc(root->left, pre, suc, key);
    } else {
        *pre = root;
        findPreSuc(root->right, pre, suc, key);
    }
}

int main() {
    Node* root = NULL;
    int ch, key;
    printf("1. Build Tree:\n");
    printf("2. Search a node:\n");
    printf("3. Find predecessor and successor of a node:\n");
    printf("4. Insert a node:\n");
    printf("5. Delete a node:\n");
    printf("6. Print Inorder Traversal:\n");
    printf("7. Exit\n");
    printf("---------------------------------\n");
    while (1) {
        printf("Enter your choice:\n");
        scanf("%d", &ch);
        if (ch == 1) {
            printf("Enter size of binary search tree:\n");
            int n;
            scanf("%d", &n);int i;
            printf("Enter nodes of binary search tree:\n");
            for (i = 0; i < n; i++) {
                scanf("%d", &key);
                root = insert(root, key);
            }
        } else if (ch == 2) {
            printf("Enter the node to search:\n");
            scanf("%d", &key);
            if (search(root, key)) printf("Found\n"); else printf("Not Found\n");
        } else if (ch == 3) {
            printf("Enter the node:\n");
            scanf("%d", &key);
            Node *pre = NULL, *suc = NULL;
            findPreSuc(root, &pre, &suc, key);
            if (pre) printf("%d ", pre->data); else printf("-1 ");
            if (suc) printf("%d\n", suc->data); else printf("-1\n");
        } else if (ch == 4) {
            printf("Enter the node:\n");
            scanf("%d", &key);
            root = insert(root, key);
        } else if (ch == 5) {
            printf("Enter the node:\n");
            scanf("%d", &key);
            root = deleteNode(root, key);
        } else if (ch == 6) {
            printf("Inorder Traversal:\n");
            inorder(root);
            printf("\n");
        } else break;
    }
    return 0;
}



