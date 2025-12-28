// External hashing using separate chaining (linked lists)

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11

typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node* table[TABLE_SIZE];

void print_table();
int hash(int key);
void insert_key(int key);
int search_key(int key);
void delete_key(int key);

int main() {
    for (int i = 0; i < TABLE_SIZE; ++i) table[i] = NULL;

    // demo
    int vals[] = {23, 43, 13, 27, 88, 44, 11};
    for (int i = 0; i < (int)(sizeof(vals)/sizeof(vals[0])); ++i) insert_key(vals[i]);

    printf("Table after inserts:\n");
    print_table();

    printf("Search 27: %s\n", search_key(27) ? "found" : "not found");
    delete_key(27);
    printf("After deleting 27:\n");
    print_table();

    delete_key(100); // delete missing
    return 0;
}

// hash function
int hash(int key) {
    return (key % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
}

void insert_key(int key) {
    int idx = hash(key);
    Node* cur = table[idx];
    while (cur) {
        if (cur->key == key) return; // no duplicates
        cur = cur->next;
    }
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->next = table[idx];
    table[idx] = n;
}

int search_key(int key) {
    int idx = hash(key);
    Node* cur = table[idx];
    while (cur) {
        if (cur->key == key) return 1;
        cur = cur->next;
    }
    return 0;
}

void delete_key(int key) {
    int idx = hash(key);
    Node* cur = table[idx];
    Node* prev = NULL;
    while (cur) {
        if (cur->key == key) {
            if (prev) prev->next = cur->next;
            else table[idx] = cur->next;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    // not found -> do nothing
}

void print_table() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        printf("%2d: ", i);
        Node* cur = table[i];
        while (cur) {
            printf("%d -> ", cur->key);
            cur = cur->next;
        }
        printf("NULL\n");
    }
}
