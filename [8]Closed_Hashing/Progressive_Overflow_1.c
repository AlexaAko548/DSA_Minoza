// Cursor-based progressive overflow for hashing.
// Primary area + overflow area. Overflow managed via a free-list (cursor).

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PRIMARY_SIZE 13
#define OVF_SIZE 7
#define TOTAL (PRIMARY_SIZE + OVF_SIZE)
#define EMPTY INT_MIN

int key_arr[TOTAL];
int next_idx[TOTAL]; // -1 means end of chain

// free-list head points to first free overflow index (in overflow region only)
int free_head = -1;

void init_table();
int hash1(int key);
int insert_key(int key);
int search_key(int key);
int delete_key(int key);
void print_table();
int allocate_overflow();
void free_overflow(int idx);

int main() {
    init_table();

    int vals[] = {12, 25, 35, 26, 14, 37, 50, 63, 76, 89, 102};
    int nvals = sizeof(vals) / sizeof(vals[0]);
    for (int i = 0; i < nvals; ++i) {
        insert_key(vals[i]);
    }

    printf("Table after inserts:\n");
    print_table();

    printf("Search 26: %s\n", search_key(26) ? "found" : "not found");
    delete_key(26);
    printf("After deleting 26:\n");
    print_table();

    insert_key(26);
    printf("After reinserting 26:\n");
    print_table();

    // Try filling overflow to show graceful fail
    insert_key(115); insert_key(128); insert_key(141); // may fill overflow
    printf("After more inserts (may fill overflow):\n");
    print_table();

    return 0;
}

/* Initialize table: primary all EMPTY, overflow chained in free-list */
void init_table() {
    for (int i = 0; i < TOTAL; ++i) {
        key_arr[i] = EMPTY;
        next_idx[i] = -1;
    }
    // build free-list for overflow area (indices PRIMARY_SIZE .. TOTAL-1)
    free_head = PRIMARY_SIZE;
    for (int i = PRIMARY_SIZE; i < TOTAL - 1; ++i) next_idx[i] = i + 1;
    next_idx[TOTAL - 1] = -1;
}

/* simple modulo hash */
int hash1(int key) {
    int h = key % PRIMARY_SIZE;
    if (h < 0) h += PRIMARY_SIZE;
    return h;
}

/* allocate an overflow slot using free-list, return index or -1 if none */
int allocate_overflow() {
    if (free_head == -1) return -1;
    int idx = free_head;
    free_head = next_idx[idx];
    next_idx[idx] = -1;
    return idx;
}

/* free an overflow slot (push back to free-list) */
void free_overflow(int idx) {
    if (idx < PRIMARY_SIZE || idx >= TOTAL) return; // safety
    key_arr[idx] = EMPTY;
    next_idx[idx] = free_head;
    free_head = idx;
}

/* insert_key: returns 1 on success, 0 on failure/duplicate */
int insert_key(int key) {
    int idx = hash1(key);

    if (key_arr[idx] == EMPTY) {
        key_arr[idx] = key;
        next_idx[idx] = -1;
        return 1;
    }
    // check duplicates and traverse chain to find last
    int cur = idx;
    while (1) {
        if (key_arr[cur] == key) return 0; // duplicate
        if (next_idx[cur] == -1) break;
        cur = next_idx[cur];
    }
    // allocate overflow slot
    int nv = allocate_overflow();
    if (nv == -1) {
        // overflow full
        return 0;
    }
    key_arr[nv] = key;
    next_idx[nv] = -1;
    next_idx[cur] = nv;
    return 1;
}

/* search_key: returns 1 if found, 0 otherwise */
int search_key(int key) {
    int idx = hash1(key);
    if (key_arr[idx] == EMPTY) return 0;
    int cur = idx;
    while (cur != -1) {
        if (key_arr[cur] == key) return 1;
        cur = next_idx[cur];
    }
    return 0;
}

/* delete_key: returns 1 if deleted, 0 if not found */
int delete_key(int key) {
    int idx = hash1(key);
    if (key_arr[idx] == EMPTY) return 0;

    // if key is at primary slot
    if (key_arr[idx] == key) {
        if (next_idx[idx] == -1) {
            // no chain: simply empty primary slot
            key_arr[idx] = EMPTY;
            return 1;
        } else {
            // promote first overflow node into primary slot
            int succ = next_idx[idx];
            key_arr[idx] = key_arr[succ];
            next_idx[idx] = next_idx[succ];
            free_overflow(succ);
            return 1;
        }
    }

    // otherwise key might be in overflow chain
    int prev = idx;
    int cur = next_idx[idx];
    while (cur != -1) {
        if (key_arr[cur] == key) {
            // unlink cur
            next_idx[prev] = next_idx[cur];
            free_overflow(cur);
            return 1;
        }
        prev = cur;
        cur = next_idx[cur];
    }
    return 0; // not found
}

/* print_table: show primary area and overflow chains + free-list */
void print_table() {
    printf("PRIMARY AREA (index : key -> next)\n");
    for (int i = 0; i < PRIMARY_SIZE; ++i) {
        if (key_arr[i] == EMPTY) printf("%2d: EMPTY\n", i);
        else printf("%2d: %d -> %d\n", i, key_arr[i], next_idx[i]);
    }

    printf("\nOVERFLOW AREA (index : key -> next)\n");
    for (int i = PRIMARY_SIZE; i < TOTAL; ++i) {
        if (key_arr[i] == EMPTY) printf("%2d: FREE\n", i);
        else printf("%2d: %d -> %d\n", i, key_arr[i], next_idx[i]);
    }

    // print free-list
    printf("\nfree-list head: %d (overflow free slots linked)\n\n", free_head);
}
