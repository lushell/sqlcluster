#include "rbtree.h"
/* Entity node, storage in array */
typedef struct _pnode {
	unsigned int id;
	char	ipv4[32];	/* Compatible ipv4 */
//	char ipv6[31];		/* Compatible ipv6 */
} pnode;

/* Max server = nodes + vnum_max */
#define nodes	0
#define vns	4

/* Rbtree wrappers */
int delete_vnode(unsigned int key, rb_node_t* root, rb_node_t* node);
int search_vnode(unsigned int key, rb_node_t* root, rb_node_t* node);
int update_vnode(unsigned int key, char *data, rb_node_t* root);
int add_vnode(rb_node_t* root, pnode *mac_node);
