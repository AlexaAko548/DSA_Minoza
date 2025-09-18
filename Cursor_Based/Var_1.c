#include <stdio.h>
#include <stdbool.h>

#define MAX 4

typedef struct {
    int elem;   // Value stored in the cell
    int next;   // Index of the next cell (-1 means null)
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;  // Array of cells acting as memory
    int avail;    // Index of the first available cell
} VHeap;

typedef int List;  // Stores the index of the head of the list

// Initialize the virtual heap
void initialize(VHeap *V) {
    V->avail = 0;  // first available cell
    for (int i = 0; i < MAX - 1; i++) {
        V->H[i].next = i + 1; // link free cells
    }
    V->H[MAX - 1].next = -1; // last cell points to "null"
}

// Allocate a new cell
int allocSpace(VHeap* V) {
    if (V->avail == -1) return -1; // no space available

    int index = V->avail;          // take the first free cell
    V->avail = V->H[index].next;   // update avail to next free
    return index;                  // return allocated index
}

// Deallocate a cell and add it back to the free list
void deallocSpace(VHeap* V, int index) {
    V->H[index].next = V->avail; // add cell back to free list
    V->avail = index;             // update avail
}

// Insert at the beginning of the list
void insertFirst(int* L, VHeap* V, int elem) {
    int newCell = allocSpace(V);
    if (newCell == -1) return; // no space

    V->H[newCell].elem = elem;
    V->H[newCell].next = *L; // point to current head
    *L = newCell;            // update head
}

// Insert at the end of the list
void insertLast(int* L, VHeap* V, int elem) {
    int newCell = allocSpace(V);
    if (newCell == -1) return;

    V->H[newCell].elem = elem;
    V->H[newCell].next = -1;

    if (*L == -1) { // empty list
        *L = newCell;
        return;
    }

    int current = *L;
    while (V->H[current].next != -1)
        current = V->H[current].next;

    V->H[current].next = newCell;
}

// Insert in sorted order
void insertSorted(int* L, VHeap* V, int elem) {
    int newCell = allocSpace(V);
    if (newCell == -1) return;

    V->H[newCell].elem = elem;

    if (*L == -1 || V->H[*L].elem >= elem) {
        V->H[newCell].next = *L;
        *L = newCell;
        return;
    }

    int current = *L;
    while (V->H[current].next != -1 && V->H[V->H[current].next].elem < elem) {
        current = V->H[current].next;
    }

    V->H[newCell].next = V->H[current].next;
    V->H[current].next = newCell;
}

// Delete by value
void delete(int* L, VHeap* V, int elem) {
    if (*L == -1) return;

    int current = *L;
    int prev = -1;

    while (current != -1 && V->H[current].elem != elem) {
        prev = current;
        current = V->H[current].next;
    }

    if (current == -1) return; // not found

    if (prev == -1) {
        *L = V->H[current].next; // delete head
    } else {
        V->H[prev].next = V->H[current].next;
    }

    deallocSpace(V, current); // return cell to free list
}

// Delete all occurrences of an element
void deleteAllOccurrence(int* L, VHeap* V, int elem) {
    int current = *L;
    int prev = -1;

    while (current != -1) {
        if (V->H[current].elem == elem) {
            if (prev == -1) {
                *L = V->H[current].next; // delete head
            } else {
                V->H[prev].next = V->H[current].next;
            }
            deallocSpace(V, current); // return cell to free list
            current = (prev == -1) ? *L : V->H[prev].next;
        } else {
            prev = current;
            current = V->H[current].next;
        }
    }
}

// Display the list
void display(int L, VHeap V) {
    int current = L;
    while (current != -1) {
        printf("%d -> ", V.H[current].elem);
        current = V.H[current].next;
    }
    printf("NULL\n");
}

int main() {
    VHeap V;
    List L = -1;  // Initially, the list is empty
    initialize(&V);

    insertFirst(&L, &V, 10);   // Insert 10 at the beginning
    insertFirst(&L, &V, 20);   // Insert 20 at the beginning
    insertLast(&L, &V, 30);    // Insert 30 at the end
    insertSorted(&L, &V, 15);  // Insert 15 in sorted order

    printf("List after inserts:\n");
    display(L, V);  // Expected output: 20 -> 10 -> 15 -> 30 -> NULL

    delete(&L, &V, 10);  // Delete element 10
    printf("List after deleting 10:\n");
    display(L, V);  // Expected output: 20 -> 15 -> 30 -> NULL

    deleteAllOccurrence(&L, &V, 15);  // Delete all occurrences of 15
    printf("List after deleting all occurrences of 15:\n");
    display(L, V);  // Expected output: 20 -> 30 -> NULL

    return 0;
}
