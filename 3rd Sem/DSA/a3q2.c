#include <stdio.h>
#include <stdlib.h>
int search(int arr[], int start, int end, int value) {
int i;
    for (i = start; i <= end; i++) if (arr[i] == value) return i;
    return -1;
}

typedef struct Node {
    int data;
    struct Node *left, *right;
}Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

Node* buildTree(int in[], int pre[], int inStart, int inEnd, int* preIndex) {
    Node* tNode;
    int inIndex;
    if (inStart > inEnd) return NULL;
    tNode = newNode(pre[*preIndex]);
    (*preIndex)++;
    if (inStart == inEnd) return tNode;
    inIndex = search(in, inStart, inEnd, tNode->data);
    tNode->left = buildTree(in, pre, inStart, inIndex - 1, preIndex);
    tNode->right = buildTree(in, pre, inIndex + 1, inEnd, preIndex);
    return tNode;
}

void printInorder(Node* node) {
    if (node == NULL) return;
    printInorder(node->left);
    printf("%d ", node->data);
    printInorder(node->right);
}


struct QNode {
    struct Node* node;
    struct QNode* next;
};

struct Queue {
    struct QNode *front, *rear;
};

struct QNode* newQNode(struct Node* treeNode) {
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->node = treeNode;
    temp->next = NULL;
    return temp;
}

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(struct Queue* q) {
    return (q->front == NULL);
}

void enQueue(struct Queue* q, struct Node* treeNode) {
    struct QNode* temp = newQNode(treeNode);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

struct Node* deQueue(struct Queue* q) {
    struct QNode* temp;
    struct Node* dequeuedNode;
    if (isEmpty(q))
        return NULL;
    temp = q->front;
    dequeuedNode = temp->node;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return dequeuedNode;
}



void printSpaces(int count) {
    int i;
    for (i = 0; i < count; i++) {
        printf(" ");
    }
}

int getHeight(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        if (leftHeight > rightHeight) {
            return (leftHeight + 1);
        } else {
            return (rightHeight + 1);
        }
    }
}


void printTreeDiagram(Node* root) {
    struct Queue* currentLevel;
    struct Queue* nextLevel;
    int totalHeight;
    int currentLevelNum;
    int nodesInThisLevel;
    int hasRealNode;
    int i;
    int initialIndent;
    int spaceBetween;

    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    currentLevel = createQueue();
    nextLevel = createQueue();
    enQueue(currentLevel, root);

    totalHeight = getHeight(root);
    currentLevelNum = 1;
    nodesInThisLevel = 1;
    hasRealNode = 1;

    while (currentLevelNum <= totalHeight && hasRealNode) {
        hasRealNode = 0;
       
        initialIndent = (1 << (totalHeight - currentLevelNum)) - 1;
        spaceBetween = (1 << (totalHeight - currentLevelNum + 1)) - 1;

        printSpaces(initialIndent);

        for (i = 0; i < nodesInThisLevel; i++) {
            struct Node* currentNode = deQueue(currentLevel);

            if (currentNode != NULL) {
                printf("%d", currentNode->data);
                enQueue(nextLevel, currentNode->left);
                enQueue(nextLevel, currentNode->right);
                if(currentNode->left != NULL || currentNode->right != NULL) {
                    hasRealNode = 1;
                }
            } else {
                printf(" ");
                enQueue(nextLevel, NULL);
                enQueue(nextLevel, NULL);
            }
            printSpaces(spaceBetween);
        }

        printf("\n\n");
        currentLevelNum++;
        nodesInThisLevel = 1 << (currentLevelNum - 1);

        free(currentLevel);
        currentLevel = nextLevel;
        nextLevel = createQueue();
    }
   
    free(currentLevel);
    free(nextLevel);
}

int main() {
    int n, i;
    int *in;
    int *pre;
    int preIndex = 0;
    Node* root;
    
    printf("Input the size of tree:\n");
    scanf("%d", &n);
    
    in = (int*)malloc(n * sizeof(int));
    pre = (int*)malloc(n * sizeof(int));
    
    if (!in || !pre) {
         printf("Memory error\n");
         return 1;
    }

    printf("Input the preorder traversal of tree:\n");
    for (i = 0; i < n; i++) scanf("%d", &pre[i]);
    printf("Input the inorder traversal of tree:\n");
    for (i = 0; i < n; i++) scanf("%d", &in[i]);
    
    root = buildTree(in, pre, 0, n - 1, &preIndex);
    printf("The given tree is:\n");
    printTreeDiagram(root);
    printf("\n");
    
    free(in);
    free(pre);
    return 0;
}
