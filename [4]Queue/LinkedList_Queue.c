#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

Queue *initialize() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}
bool isEmpty(Queue *q);
void enqueue(Queue *q, int val);
int dequeue(Queue *q);
int front(Queue *q);
void display(Queue *q);

int main() {
    Queue *q = initialize();
    
    printf("Queue: ");
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    display(q);
    
    int del = dequeue(q);
    if(del == -1) {
        printf("Cannot dequeue since queue is empty.\n");
    } else {
        printf("%d has been dequeued.", del);   
    }
    printf("\nQueue: ");
    display(q);
    
    
    return 0;
}

bool isEmpty(Queue *q) {
    return q->front == NULL;
}
void enqueue(Queue *q, int val) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}
int dequeue(Queue *q) {
    if (!isEmpty(q)) {
        Node *temp = q->front;
        int val = temp->data;
        q->front = q->front->next;
        
        if (q->front == NULL) {
            q->rear = NULL;
        }
        
        free(temp);
        return val;
    } return -1;
}
int front(Queue *q) {
    if (!isEmpty(q)) {
        return q->front->data;
    }
}
void display(Queue *q) {
    if (!isEmpty(q)) {
        Node *i = q->front;
        while (i != NULL) {
            printf("%d ", i->data);
            i = i->next;
        }
        printf("\n");
    }
}