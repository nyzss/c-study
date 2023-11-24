
typedef struct node_t {
  int data;
  char *key;
  struct node_t *next;
} node_t;

typedef struct hashmap {
  int len;
  node_t **buckets;
} hashmap;

hashmap create_map(int);

node_t *create_node(char *, int);

int hash(char *, int);

int check_hash(hashmap *, int);

void push(hashmap *, char *, int);

void remove_ht(hashmap *, char *);

void remove_val(hashmap *, int);

void print_hashmap(hashmap *);
