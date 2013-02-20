typedef long int hash_key;
typedef char * data_t;

typedef enum color_t
{
    RED = 0,
    BLACK = 1
} color_t;

typedef struct rb_node_t
{
    struct rb_node_t *left, *right, *parent;
    hash_key key;
    data_t data;
    color_t color;
} rb_node_t;

rb_node_t* rb_insert(hash_key key, data_t data, rb_node_t* root);
rb_node_t* rb_search(hash_key key, rb_node_t* root);
rb_node_t* rb_delete(hash_key key, rb_node_t* root);
hash_key rb_update(hash_key key, rb_node_t* root, data_t data);
