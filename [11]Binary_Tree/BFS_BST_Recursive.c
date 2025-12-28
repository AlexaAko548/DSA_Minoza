// using level-order traversal (BFS) recursively on a BST

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// prototypes
Node* insert(Node* root, int x);
int height(Node* root);
void printLevel(Node* root, int level);
void bfs(Node* root);

int main() {
    Node* root = NULL;
    int a[] = {50, 30, 70, 20, 40, 60, 80};

    for (int i = 0; i < 7; i++)
        root = insert(root, a[i]);

    printf("BFS (recursive): ");
    bfs(root);
    printf("\n");

    return 0;
}

Node* insert(Node* root, int x) {
    if (!root) {
        Node* n = malloc(sizeof(Node));
        n->data = x; n->left = n->right = NULL;
        return n;
    }
    if (x < root->data)
        root->left = insert(root->left, x);
    else
        root->right = insert(root->right, x);
    return root;
}

int height(Node* root) {
    if (!root) return 0;
    int l = height(root->left);
    int r = height(root->right);
    return (l > r ? l : r) + 1;
}

void printLevel(Node* root, int level) {
    if (!root) return;
    if (level == 1)
        printf("%d ", root->data);
    else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void bfs(Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++)
        printLevel(root, i);
}
