#include <stdio.h>
#include <stdlib.h>

struct node_t {
  int data;
  struct node_t *next;
};

typedef struct node_t node_t;

node_t *create_empty() {
  node_t *node = (node_t *)malloc(sizeof(node_t));

  return node;
}

node_t *create(int data) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->data = data;
  node->next = NULL;

  return node;
}

// front push
void push(node_t *node, int value) {

  node_t *new_node = create(value);

  new_node->next = node;

  *node = *new_node;
}

void push_back(node_t *node, int value) {

  node_t *new_node = create(value);

  // we initialize tmp with the head of the linked list's pointer, then in the
  // while loop we update tmp with the pointer of the next node of the linked
  // list, thefore getting something like: node->next->next.. and so on. the
  // head pointer remains unchanged since we just updated a local copy of the
  // pointer and we haven't touched the head node pointer.
  node_t *tmp = node;

  while (tmp->next != NULL) {
    tmp = tmp->next;
  }

  tmp->next = new_node;
}

// front pop
void pop(node_t *node) {

  if (node == NULL) {
    return;
  }

  node_t *tmp_current = node;

  node_t *tmp_next = node->next;

  *node = *tmp_next;
  free(tmp_current);
}

// TODO:
void pop_back(node_t *node) {
  node_t *tmp = node;
  // NOTE: get the one before the latest -> change it to latest (which is stored
  // in a tmp)

  // NOTE: returns the node just before the last one (so the new latest node
  // after popping the current last one)
  while (tmp->next->next != NULL) {
    tmp = tmp->next;
  };
  node_t *last = tmp->next;

  tmp->next = NULL;
  free(last);
}

void push_back_multiple(node_t *node, int arr[], int len) {
  node_t *tmp = node;
  // get last node
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }

  for (int i = 0; i < len; i++) {
    node_t *n_node = create(arr[i]);
    tmp->next = n_node;
    tmp = tmp->next;
  }
}

void remove_val(node_t *node, int val) {
  // if it's the first one then we just pop it out.
  if (node->data == val) {
    pop(node);
  }

  // iterate over the linked list, if the next node has the data that we are
  // looking for then we set the current node's pointer to the one that is next
  // to the one we found.
  for (node_t *t = node; t != NULL; t = t->next) {
    if (t->next->data == val) {
      t->next = t->next->next;
    }
  }
}

void print_ll(node_t *node) {
  node_t *tmp = node;

  int count = 0;
  while (tmp != NULL) {
    printf("data: %d\n", tmp->data);
    tmp = tmp->next;
    count++;
  }
  printf("count: %d", count);
}

int main() {

  node_t *node = create(5);
  int arr[] = {123, 667, 8834, 903, 112};
  int len = sizeof(arr) / sizeof(arr[0]);
  push_back_multiple(node, arr, len);
  pop_back(node);

  remove_val(node, 903);

  print_ll(node);
}
