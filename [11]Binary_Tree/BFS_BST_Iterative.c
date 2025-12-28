// using queue to perform BFS traversal on a BST

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// queue
Node* q[MAX];
int front = 0, rear = 0;

// prototypes
Node* insert(Node* root, int x);
int isMember(Node* root, int x);
Node* delete(Node* root, int x);
Node* left(Node* root);

void bfs(Node* root);

Node* findMin(Node* root);

int main() {
    Node* root = NULL;
    int a[] = {50, 30, 70, 20, 40, 60, 80};

    for (int i = 0; i < 7; i++)
        root = insert(root, a[i]);

    printf("BFS: ");
    bfs(root);
    printf("\n");

    return 0;
}

Node* insert(Node* root, int x) {
    Node* n = malloc(sizeof(Node));
    n->data = x; n->left = n->right = NULL;
    if (!root) return n;

    Node* cur = root;
    while (1) {
        if (x < cur->data) {
            if (!cur->left) { cur->left = n; break; }
            cur = cur->left;
        } else {
            if (!cur->right) { cur->right = n; break; }
            cur = cur->right;
        }
    }
    return root;
}

void bfs(Node* root) {
    if (!root) return;

    q[rear++] = root;
    while (front < rear) {
        Node* cur = q[front++];
        printf("%d ", cur->data);
        if (cur->left) q[rear++] = cur->left;
        if (cur->right) q[rear++] = cur->right;
    }
}

int isMember(Node* root, int x) {
    return root && (root->data == x ||
           isMember(root->left, x) ||
           isMember(root->right, x));
}

Node* left(Node* root) {
    return root ? root->left : NULL;
}
