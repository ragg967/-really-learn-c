#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  void *data;
  struct Node *nextNode;
};

struct LinkedList {
  int nodeCount;
  struct Node *list[];
};

struct LinkedList InitLinkedList(int nodeCount);
void *listGetData(struct LinkedList list, int index);
void listAppend(struct LinkedList list, void *data);

int main(void) {
  struct LinkedList list = InitLinkedList(10);
  
  printf("%d", (int)(size_t)listGetData(list, 0));
}

void listAppend(struct LinkedList list, void *data) {
  struct Node *newNode = malloc(sizeof(struct Node));
  newNode->data = data;
  list.list[list.nodeCount + 1] = newNode;
}

void *listGetData(struct LinkedList list, int index) {
  for (size_t i = 0; i < index; i++) {
    if (i == index)
      return list.list[i];
  }
  return NULL;
}

struct LinkedList InitLinkedList(int nodeCount) {
  struct LinkedList list;
  list.nodeCount = nodeCount;
  struct Node *head = NULL;
  struct Node *current = NULL;

  for (int i = 0; i < nodeCount; i++) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = 0;
    newNode->nextNode = NULL;

    if (head == NULL) {
      head = newNode;
      current = head;
    } else {
      current->nextNode = newNode;
      current = newNode;
    }
  }

  list.list[0] = head;
  return list;
}
