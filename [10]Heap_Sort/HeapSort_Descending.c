// Heap Sort using Min-Heap (Struct-based)

#include <stdio.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int size;
} Heap;

// prototypes
void swap(int *a, int *b);
void print(Heap *h);

int main() {
    Heap h;
    h.size = 6;

    // input array
    h.items[0] = 12;
    h.items[1] = 11;
    h.items[2] = 13;
    h.items[3] = 5;
    h.items[4] = 6;
    h.items[5] = 7;

    printf("Before sorting:\n");
    print(&h);

    /* BUILD MIN HEAP */
    for (int i = (h.size / 2) - 1; i >= 0; i--) {
        int parent = i;

        while (1) {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int smallest = parent;

            if (left < h.size && h.items[left] < h.items[smallest])
                smallest = left;
            if (right < h.size && h.items[right] < h.items[smallest])
                smallest = right;

            if (smallest == parent) break;

            swap(&h.items[parent], &h.items[smallest]);
            parent = smallest;
        }
    }

    /* HEAP SORT */
    for (int end = h.size - 1; end > 0; end--) {
        swap(&h.items[0], &h.items[end]);

        int parent = 0;
        while (1) {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int smallest = parent;

            if (left < end && h.items[left] < h.items[smallest])
                smallest = left;
            if (right < end && h.items[right] < h.items[smallest])
                smallest = right;

            if (smallest == parent) break;

            swap(&h.items[parent], &h.items[smallest]);
            parent = smallest;
        }
    }

    printf("After sorting (descending):\n");
    print(&h);

    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print(Heap *h) {
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->items[i]);
    }
    printf("\n");
}
