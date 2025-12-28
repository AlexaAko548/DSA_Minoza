#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// prototypes
Node* insert(Node* root, int x);
int isMember(Node* root, int x);
Node* delete(Node* root, int x);
Node* left(Node* root);

void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);

// helpers
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

    printf("Is 60 member? %d\n", isMember(root, 60));

    root = delete(root, 50);
    printf("After deleting 50 (inorder): ");
    inorder(root); printf("\n");

    return 0;
}

Node* insert(Node* root, int x) {
    if (!root) {
        Node* n = malloc(sizeof(Node));
        n->data = x;
        n->left = n->right = NULL;
        return n;
    }
    if (x < root->data)
        root->left = insert(root->left, x);
    else if (x > root->data)
        root->right = insert(root->right, x);
    return root;
}

int isMember(Node* root, int x) {
    if (!root) return 0;
    if (root->data == x) return 1;
    if (x < root->data) return isMember(root->left, x);
    return isMember(root->right, x);
}

Node* findMin(Node* root) {
    while (root->left) root = root->left;
    return root;
}

Node* delete(Node* root, int x) {
    if (!root) return NULL;

    if (x < root->data)
        root->left = delete(root->left, x);
    else if (x > root->data)
        root->right = delete(root->right, x);
    else {
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

Node* left(Node* root) {
    if (!root) return NULL;
    return root->left;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}
