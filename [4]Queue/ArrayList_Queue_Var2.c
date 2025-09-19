#define MAX 10
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

Queue *initialize() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}
bool isFull(Queue *q);
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

bool isFull(Queue *q) {
    return q->front == (q->rear + 1) % MAX;
}
bool isEmpty(Queue *q) {
    return q->front == -1;
}
void enqueue(Queue *q, int val) {
    if (!isFull(q)) {
        if(isEmpty(q)) {
            q->front = 0;
        } 
        q->rear = (q->rear + 1) % MAX;
        q->items[q->rear] = val;
    }
}
int dequeue(Queue *q) {
    if (!isEmpty(q)) {
        int val = q->items[q->front];
        if (q->front == q->rear) {
            q->front = q->rear = -1;
        }
        q->front = (q->front + 1) % MAX;
        return val;
    } return -1;
}
int front(Queue *q) {
    if (!isEmpty(q)) {
        return q->items[q->front];
    }
}
void display(Queue *q) {
    if (!isEmpty(q)) {
        int i = q->front;
        while (i != q->rear) {
            printf("%d ", q->items[i]);
            i = (i + 1) % MAX;
        }
        printf("%d\n", q->items[q->rear]);
    }
}