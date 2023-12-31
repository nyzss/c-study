#include "c_hashmap.h"
#include <stdio.h>
#include <stdlib.h>

// TODO: Implement a free hashmap func
// TODO: Dynamically resize hashmap and re-hash every single key-value pair.
// TODO: Use my own linked_list.c implementation with the hashmap

size_t m_strlen(char *str) {
  int count = 0;
  while (str[count]) {
    count++;
  }
  return count;
}

hashmap create_map(int initial_size) {
  node_t **ll_arr = (node_t **)malloc(initial_size * sizeof(node_t));

  for (int i = 0; i < initial_size; i++) {
    ll_arr[i] = NULL;
  }

  hashmap ht = {.len = initial_size, .buckets = ll_arr};

  return ht;
}

node_t *create_node(char *key, int data) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->key = key;
  new_node->data = data;
  new_node->next = NULL;

  return new_node;
}

// some random hash function that I thought of since I was too lazy to look up
// and implement one takes the char number of each of the string's char,
// multiply it by the index +1 (to negatate the 0 index) and sum it all up to
// then modulo it to the array len so lets say the key is "car" and the hashmap
// length is 15, it goes like this: 99 * 1 + 97 * 2 + 114 * 3 = 635 % 15 = 5
// so the index is 9
int hash(char *key, int ht_len) {
  int hashed;
  int str_length = m_strlen(key);

  int sum = 0;

  for (int i = 0; i < str_length; i++) {
    int c = key[i];
    sum += c * (i + 1);
  }

  hashed = sum % ht_len;

  return hashed;
}

// return 1 if exist, and return 0 if doesn't exist.
int check_hash(hashmap *ht, int index) {
  if (ht->buckets[index] == NULL) {
    return 0;
  }

  return 1;
}

void push(hashmap *ht, char *key, int data) {
  int len = ht->len;

  int index = hash(key, len);

  node_t *node = create_node(key, data);

  if (!check_hash(ht, index)) {
    ht->buckets[index] = node;
  } else {
    node_t *tmp = ht->buckets[index];

    while (tmp->next != NULL) {
      tmp = tmp->next;
    }

    tmp->next = node;
  }
}

void remove_key(hashmap *ht, char *key) {
  int idx = hash(key, ht->len);

  ht->buckets[idx] = NULL;
}

void remove_val(hashmap *ht, int val) {

  for (int i = 0; i < ht->len; i++) {

    node_t *head = ht->buckets[i];
    if (head != NULL) {
      if (head->data == val) {
        if (head->next != NULL) {
          ht->buckets[i] = head->next;
        } else {
          ht->buckets[i] = NULL;
        }
      }
    }

    for (node_t *t = head; t != NULL; t = t->next) {

      if (t->next != NULL && t->next->data == val) {
        t->next = t->next->next;
      }
    }
  }
}

void print_hashmap(hashmap *ht) {

  for (int i = 0; i < ht->len; i++) {
    node_t *tmp = ht->buckets[i];

    while (tmp != NULL) {
      printf("index: %d, key: %s, data: %d\n", i, tmp->key, tmp->data);
      tmp = tmp->next;
    }
  }
}

int main() {

  hashmap hmap = create_map(15);
  hashmap *ht = &hmap;

  push(ht, "car", 150123);
  push(ht, "hello world", 100);
  push(ht, "cool carand stuff", 75630);
  push(ht, "same hash", 1);
  push(ht, "same hash", 500);

  // remove_key(ht, "car");
  // remove_val(ht, 500);
  remove_val(ht, 100);
  print_hashmap(ht);
}
