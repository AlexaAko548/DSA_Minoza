//added pushUnique and popUnique

#define MAX 10
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int elem[MAX];
    int top;
} Stack;    

void initialize(Stack *S);
bool isFull(Stack *S);
bool isEmpty(Stack *S);
void push(Stack *S, int elem);
void pushUnique(Stack *S, int elem);
int pop(Stack *S);
void popUnique(Stack *S, int elem);
int peek(Stack *S);
int top(Stack *S);
void display(Stack *S);

int main() {
    Stack S;
    initialize(&S);
    
    printf("Push:\n");
    push(&S, 10);
    push(&S, 20);
    push(&S, 30);
    display(&S);
    
    printf("\nPop:\n");
    pop(&S);
    display(&S);
    
    printf("\nPush Unique:\n");
    pushUnique(&S, 20);
    pushUnique(&S, 40);
    display(&S);
    
    printf("\nPop Unique:\n");
    popUnique(&S, 80);
    popUnique(&S, 10);
    display(&S);
    
    
    return 0;
}

void initialize(Stack *S) {
    S->top = -1;
}
bool isFull(Stack *S) {
    return S->top == MAX - 1;
}
bool isEmpty(Stack *S) {
    return S->top == -1;
}
void push(Stack *S, int elem){
    if (!isFull(S)) {
        S->elem[++S->top] = elem;
    }
    return;
}
void pushUnique(Stack *S, int elem) {
    if (isFull(S)) return;
        Stack temp;
        initialize(&temp);
        
        bool found = false;
        while(!isEmpty(S)) {
            int topElem = pop(S);
            if (topElem == elem) {
                found = true;
            }
            push(&temp, topElem); //push to temporary stack     
        }
        
        if (!found) {
            push(S, elem);
        }
        
        while (!isEmpty(&temp)) {
            push(S, pop(&temp)); //push back the temp stack to the 
        }                           //orig stack
}
int pop(Stack *S) {
    if (!isEmpty(S)) {
        int val = S->elem[S->top];
        S->top--;
        return val;
    }
    return -1;
}
void popUnique(Stack *S, int elem) {
    if (isEmpty(S)) return;
        Stack temp;
        initialize(&temp);
        
        bool found = false;
        while(!isEmpty(S)) {
            int topElem = pop(S);
            if (topElem == elem && !found) {
                found = true;
            } else {
                push(&temp, topElem);//push remaining elems to temp stack 
            }
        }
        
        while(!isEmpty(&temp)) {
            push(S, pop(&temp));
        }
}
int peek(Stack *S) {
    if (!isEmpty(S)) {
        return S->elem[S->top];
    }
    return -1;
}
int top(Stack *S) {
    return S->top;
}
void display(Stack *S) {
    for (int i = S->top; i >= 0; i--) {
        printf("%d\n", S->elem[i]);
    }
}