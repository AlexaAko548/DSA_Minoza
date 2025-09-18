#define MAX 10
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int items[MAX];
    int top;
} Stack;

void initialize(Stack *s);
bool isFull(Stack *s);
bool isEmpty(Stack *s);
void push(Stack *s, int value);
int pop(Stack *s);
int peek(Stack *s);
int top(Stack *s);
void display(Stack* s);

int main() {
    Stack S;
    initialize(&S);
    
    push(&S, 10);
    push(&S, 20);
    push(&S, 30);
    
    display(&S);
    
    pop(&S);
    printf("\n");
    display(&S);
    
    
    return 0;
}

void initialize(Stack *s) {
    s->top = -1;
}
bool isFull(Stack *s) {
    return s->top == MAX-1;
}
bool isEmpty(Stack *s) {
    return s->top == -1;
}
void push(Stack *s, int value) {
    if (!isFull(s)) {
        s->top++;
        s->items[s->top] = value;
    } else {
        return;
    }
}
int pop(Stack *s) {
    if (!isEmpty(s)) {
        int val = s->items[s->top];
        s->top--;
        return val;
    } else {
        return -1;
    }
}
int peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    } else {
        return -1;
    }
}
int top(Stack *s) {
    return s->top;
}
void display(Stack* s) {
    if (!isEmpty(s)) {
        int Top = top(s);
        for (int i = Top; i >= 0; i--) {
            printf("%d\n", s->items[i]);
        }
    } else {
        printf("Stack is empty...");
    }
}