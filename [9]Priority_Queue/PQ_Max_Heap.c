// Priority Queue using Max-Heap (Struct-based)
// Functions allowed: enqueue, dequeue, swap, print

#include <stdio.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int size;
} PrioQ;

// prototypes
void enqueue(PrioQ *pq, int x);
int dequeue(PrioQ *pq);
void swap(int *a, int *b);
void print(PrioQ *pq);

int main() {
    PrioQ pq;
    pq.size = 0;

    int arr[] = {20, 5, 15, 22, 40, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        enqueue(&pq, arr[i]);
    }

    printf("Heap after enqueue:\n");
    print(&pq);

    printf("Dequeued max: %d\n", dequeue(&pq));
    printf("Heap after dequeue:\n");
    print(&pq);

    return 0;
}

void enqueue(PrioQ *pq, int x) {
    if (pq->size == MAX) return;

    int i = pq->size;
    pq->items[i] = x;
    pq->size++;

    // bubble up
    while (i > 0 && pq->items[i] > pq->items[(i - 1) / 2]) {
        swap(&pq->items[i], &pq->items[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int dequeue(PrioQ *pq) {
    if (pq->size == 0) return -1;

    int max = pq->items[0];
    pq->items[0] = pq->items[pq->size - 1];
    pq->size--;

    // bubble down
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < pq->size && pq->items[left] > pq->items[largest])
            largest = left;
        if (right < pq->size && pq->items[right] > pq->items[largest])
            largest = right;
        if (largest == i) break;

        swap(&pq->items[i], &pq->items[largest]);
        i = largest;
    }

    return max;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print(PrioQ *pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("%d ", pq->items[i]);
    }
    printf("\n");
}
