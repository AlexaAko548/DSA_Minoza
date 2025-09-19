#define MAX 10
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int items[MAX];
    int count;
} List;

typedef struct {
    List list;
    int front;
    int rear;
} Queue;

Queue *initialize() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->list.count = 0;
    q->front = q->rear = -1;
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
    return q->list.count == MAX;
}
bool isEmpty(Queue *q) {
    return q->list.count == 0;
}
void enqueue(Queue *q, int val) {
    if (!isFull(q)) {
        if(isEmpty(q)) {
            q->front = q->rear = 0;
        } else {
            q->rear = (q->rear + 1) % MAX;
        }
        q->list.items[q->rear] = val;
        q->list.count++;
    }
}
int dequeue(Queue *q) {
    if (!isEmpty(q)) {
        int val = q->list.items[q->front];
        if (q->front == q->rear) {
            q->front = q->rear = -1;
        } else {
            q->front = (q->front + 1) % MAX;
        }
        q->list.count--;
        return val;
    } return -1;
}
int front(Queue *q) {
    if (!isEmpty(q)) {
        return q->list.items[q->front];
    }
}
void display(Queue *q) {
    if (!isEmpty(q)) {
        int i = q->front;
        for (int j = 0; j < q->list.count; j++) {
            printf("%d ", q->list.items[i]);
            i = (i + 1) % MAX;
        }
        printf("\n");
    }
}