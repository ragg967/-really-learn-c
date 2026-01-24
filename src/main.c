#include "strings.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INT_TO_PTR(a) ((void *)(intptr_t)a)

struct Node {
  const char *key;
  void *value;
  struct Node *next;
} Node;

struct HashTable {
  size_t capacity;
  struct Node slots[];
} HashTable;

struct HashTable *initHashTable(void);
void hashAddNode(struct HashTable *hashTable, const char *key, void *data);
void *hashGetValue(struct HashTable *hashTable, const char *key);
size_t hash(struct HashTable *hashTable, const char *key);

int main(void) {
  struct HashTable *hashTable = initHashTable();

  hashAddNode(hashTable, "Bob", INT_TO_PTR(10));
  hashAddNode(hashTable, "Alice", (void *)"Baller name");
  hashAddNode(hashTable, "Charlie", INT_TO_PTR(true));

  printf("Bob: %d\n", (int)(size_t)hashGetValue(hashTable, "Bob"));
  printf("Alice: %s\n", (char *)hashGetValue(hashTable, "Alice"));
  printf("Charlie: %s\n",
         (bool)hashGetValue(hashTable, "Charlie") ? "true" : "false");

  void *result = hashGetValue(hashTable, "David");
  if (result == NULL) {
    printf("David: not found\n");
  }

  return 0;
}

size_t hash(struct HashTable *hashTable, const char *key) {
  size_t hash = 0;
  while (*key) {
    hash = hash * 31 + *key;
    key++;
  }
  return hash % hashTable->capacity;
}

void *hashGetValue(struct HashTable *hashTable, const char *key) {
  size_t hashedKey = hash(hashTable, key);
  struct Node *current = &hashTable->slots[hashedKey];

  while (current != NULL) {
    if (current->key != NULL && !strcasecmp(current->key, key)) {
      return current->value;
    }
    current = current->next;
  }

  return NULL;
}
void hashAddNode(struct HashTable *hashTable, const char *key, void *data) {
  size_t hashedKey = hash(hashTable, key);

  if (hashTable->slots[hashedKey].key == NULL) {
    hashTable->slots[hashedKey].key = key;
    hashTable->slots[hashedKey].value = data;
    hashTable->slots[hashedKey].next = NULL;
  } else {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = data;
    newNode->next = NULL;
    hashTable->slots[hashedKey].next = newNode;
  }
}

struct HashTable *initHashTable(void) {
  struct HashTable *hashTable = malloc(sizeof(HashTable) + 256 * sizeof(Node));
  hashTable->capacity = 256;

  for (unsigned short i = 0; i < hashTable->capacity; i++) {
    hashTable->slots[i].key = NULL;
    hashTable->slots[i].value = NULL;
    hashTable->slots[i].next = NULL;
  }

  return hashTable;
}
