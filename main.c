#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *data;
  int len;
  int capacity;
} c_vector;

int resize_vec(c_vector **);
c_vector new_vec(int);
void push_single(c_vector *, int);
void push_multiple(c_vector *, int[], int);
c_vector from_arr(int[], int);
void print_vec(c_vector);

c_vector new_vec(int initial_capacity) {
  int *arr = (int *)malloc(initial_capacity * sizeof(int));

  c_vector vec = {.data = arr, .len = 0, .capacity = initial_capacity};

  return vec;
}

void push_single(c_vector *vec, int data) {
  resize_vec(&vec);

  vec->data[vec->len] = data;

  vec->len += 1;
}

void push_multiple(c_vector *vec, int data[], int data_len) {
  if (vec->len + data_len >= vec->capacity) {
    vec->capacity *= 2;
    vec->capacity += data_len;
    vec->data = realloc(vec->data, vec->capacity * sizeof(int));
  }

  for (int i = 0; i < data_len; i++) {
    push_single(vec, data[i]);
  }

  // this might work and might perform better (or the same lol)
  // have to try it out later on
  // for (int i = vec->len; i< vec->len + data_len; i++) {
  //
  // }
}

int resize_vec(c_vector **vector) {
  c_vector *vec = *vector;
  if (vec->len == vec->capacity) {
    vec->capacity *= 2;
    vec->data = (int *)realloc(vec->data, vec->capacity * sizeof(int));
    if (vec->data == NULL) {
      return 0;
    }
    return 1;
  }
  return 0;
}

c_vector from_arr(int data[], int len) {
  int capacity = 2 * len;
  c_vector vec = new_vec(capacity);

  push_multiple(&vec, data, len);

  return vec;
}

void print_vec(c_vector vec) {
  printf("--------------------------\n");
  printf("len: %d\n", vec.len);
  printf("cap: %d\n", vec.capacity);
  printf("  --  \n");
  for (int i = 0; i < vec.len; i++) {
    printf("idx: %d, value: %d\n", i, vec.data[i]);
  }
  printf("--------------------------\n");
}

int main() {
  c_vector vec = new_vec(3);

  push_single(&vec, 101203);
  push_single(&vec, 1234);
  int arr[4] = {223, 99, 66, 1379};
  push_multiple(&vec, arr, 4);

  print_vec(vec);

  int some_arr[5] = {123182, 46540, 11, 0, 234};

  c_vector vec_2 = from_arr(some_arr, 5);
  push_single(&vec_2, 100);

  print_vec(vec_2);
}
