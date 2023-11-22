
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

void free_vec(c_vector *);
