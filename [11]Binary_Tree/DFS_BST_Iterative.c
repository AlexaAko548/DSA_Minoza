// using stack to perform iterative DFS traversals (inorder, preorder, postorder) on a BST

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// stack
Node* stack[MAX];
int top = -1;

// prototypes
Node* insert(Node* root, int x);
int isMember(Node* root, int x);
Node* delete(Node* root, int x);
Node* left(Node* root);

void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);

Node* findMin(Node* root);

int main() {
    Node* root = NULL;

    int a[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++)
        root = insert(root, a[i]);

    printf("Inorder: ");
    inorder(root); printf("\n");

    printf("Preorder: ");
    preorder(root); printf("\n");

    printf("Postorder: ");
    postorder(root); printf("\n");

    return 0;
}

/* same BST operations as recursive version */
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

int isMember(Node* root, int x) {
    while (root) {
        if (root->data == x) return 1;
        root = (x < root->data) ? root->left : root->right;
    }
    return 0;
}

Node* left(Node* root) {
    return root ? root->left : NULL;
}

/* ITERATIVE TRAVERSALS */
void inorder(Node* root) {
    Node* cur = root;
    while (cur || top != -1) {
        while (cur) {
            stack[++top] = cur;
            cur = cur->left;
        }
        cur = stack[top--];
        printf("%d ", cur->data);
        cur = cur->right;
    }
}

void preorder(Node* root) {
    if (!root) return;
    stack[++top] = root;

    while (top != -1) {
        Node* cur = stack[top--];
        printf("%d ", cur->data);
        if (cur->right) stack[++top] = cur->right;
        if (cur->left) stack[++top] = cur->left;
    }
}

void postorder(Node* root) {
    Node* last = NULL;
    Node* cur = root;

    while (cur || top != -1) {
        if (cur) {
            stack[++top] = cur;
            cur = cur->left;
        } else {
            Node* peek = stack[top];
            if (peek->right && last != peek->right)
                cur = peek->right;
            else {
                printf("%d ", peek->data);
                last = stack[top--];
            }
        }
    }
}
