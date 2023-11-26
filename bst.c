#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  int data;
  struct node_t *left;
  struct node_t *right;

} node_t;

node_t *create_node(int data) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->data = data;

  node->left = NULL;
  node->right = NULL;

  return node;
}

void push(node_t *tree, int data) {
  node_t *tmp = tree;

  node_t *new_node = create_node(data);

  if (data < tmp->data) {
    if (tmp->left != NULL) {
      tmp = tmp->left;
      push(tmp, data);
    }
    tmp->left = new_node;
  }

  if (data > tmp->data) {
    if (tmp->right != NULL) {
      tmp = tmp->right;
      push(tmp, data);
    }
    tmp->right = new_node;
  }

  // while (tmp != NULL) {
  //   if (data < tmp->data) {
  //     tmp = tmp->left;
  //   } else if (data > tmp->data) {
  //     tmp = tmp->right;
  //   }
  // };

  tmp = new_node;
}

void print_tree(node_t *tree) {
  node_t *tmp = tree;

  if (tmp) {
    printf("tree data: %d\n", tmp->data);
    print_tree(tmp->left);
    print_tree(tmp->right);
  }
}

int main() {
  node_t *btree = create_node(599);

  push(btree, 500);
  push(btree, 12401);
  push(btree, 22);
  push(btree, 800);
  push(btree, 1);

  print_tree(btree);
}
