#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INT_TO_PTR(a) ((void *)(intptr_t)a)

struct Node {
  void *data;
  struct Node *nextNode;
};

struct LinkedList {
  size_t nodeCount;
  struct Node *list[];
};

struct LinkedList *InitLinkedList(size_t nodeCount);
void *listGetData(struct LinkedList *list, size_t index);
void listAppend(struct LinkedList *list, size_t index, void *data);

int main(void) {
  struct LinkedList *list = InitLinkedList(10);
  listAppend(list, 0, INT_TO_PTR(10));
  printf("%d", (int)(size_t)listGetData(list, 0));
}

void listAppend(struct LinkedList *list, size_t index, void *data) {
  struct Node *newNode = malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->nextNode = NULL;
  list->list[index] = newNode;
}

void *listGetData(struct LinkedList *list, size_t index) {
  for (size_t i = 0; i < index; i++) {
    if (i == index)
      return list->list[i];
  }
  return NULL;
}

struct LinkedList *InitLinkedList(size_t nodeCount) {
  struct LinkedList *list =
      malloc(sizeof(struct LinkedList) + sizeof(struct Node) * nodeCount);
  list->nodeCount = nodeCount;

  for (size_t i = 0; i < list->nodeCount; i++) {
    list->list[i]->data = NULL;
    list->list[i]->nextNode = NULL;
  }

  return list;
}
