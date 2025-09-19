#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

Stack* initialize() {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

bool isFull(Stack *s);
bool isEmpty(Stack *s);
void push(Stack *s, int elem);
void pushUnique(Stack *s, int elem);
int pop(Stack *s);
void popUnique(Stack *s, int elem);
int peek(Stack *s);
void display(Stack *s);

int main() {
    Stack *S = initialize();

    printf("Push 10, 20, 30\n");
    push(S, 10);
    push(S, 20);
    push(S, 30);
    display(S);                     // [top] 30 -> 20 -> 10 -> NULL

    printf("\nPeek: %d\n", peek(S));  // 30

    printf("\nPop: %d\n", pop(S));    // 30
    display(S);                     // [top] 20 -> 10 -> NULL

    printf("\npushUnique 20 (duplicate)\n");
    pushUnique(S, 20);              // no change
    display(S);                     // [top] 20 -> 10 -> NULL

    printf("\npushUnique 40\n");
    pushUnique(S, 40);
    display(S);                     // [top] 40 -> 20 -> 10 -> NULL

    printf("\npopUnique 20\n");
    popUnique(S, 20);
    display(S);                     // [top] 40 -> 10 -> NULL

    printf("\nPop all:\n");
    while (!isEmpty(S)) {
        printf("  popped %d\n", pop(S));
    }
    display(S);
    
    
    return 0;
}

bool isFull(Stack *s) {
    return false;
}
bool isEmpty(Stack *s) {
    return s->top == NULL;
}
void push(Stack *s, int elem) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = elem;
    newNode->next = s->top;
    s->top = newNode;
}
void pushUnique(Stack *s, int elem) {
    Node *p;
    for (p = s->top; p && p->data != elem; p = p->next) {}
    if (p == NULL) {
        push(s, elem);
    }
}
int pop(Stack *s) {
    if (!isEmpty(s)) {
        Node *temp = s->top;
        int val = temp->data;
        s->top = temp->next;
        free(temp);
        return val;
    } return -1;
}
void popUnique(Stack *s, int elem) {
    Node **pp, *del;
    
    for (pp = &s->top; *pp && (*pp)->data != elem; pp = &(*pp)->next){}
    if(*pp) {
        del = *pp;
        *pp = del->next;
        free(del);
    }
}
int peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->top->data;
    } return -1;
}
void display(Stack *s) {
    if (!isEmpty(s)) {
        Node *temp;
        for (temp = s->top; temp; temp = temp->next){
            printf("%d\n", temp->data);
        }
    }
}