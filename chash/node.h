#include "rbtree.h"
/* Virtual node number */
#define vns	4
/* Entity node, storage in array */
typedef struct _pnode {
	unsigned int id;
	hash_key vkey[vns];
	char	ipv4[32];	/* Compatible ipv4 */
//	char ipv6[31];		/* Compatible ipv6 */
} pnode;

/* Max server = nodes + vnum_max */
#define nodes	0
#define max_node 0xfff

/* Rbtree wrappers */
int delete_vnode(unsigned int key, rb_node_t* root, rb_node_t* node);
int search_vnode(unsigned int key, rb_node_t* root, rb_node_t* node);
int update_vnode(unsigned int key, char *data, rb_node_t* root);
int add_vnode(rb_node_t* root, pnode *mac_node);
int generate_vkey(pnode *mac_node);
