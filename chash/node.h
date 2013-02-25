#include "rbtree.h"
#include "md5hash.h"
/* Entity node, storage in array */
typedef struct _pnode {
	unsigned int id;
	char	ipv4[14];	/* Compatible ipv4 */
//	char ipv6[31];		/* Compatible ipv6 */
} pnode;

/* Max server = nodes + vnum_max */
#define nodes	0
#define vnum_max	4	/* Eentity node mapping to virtual node */
#define max_nodes	0xfff	/* Max node */

/* Rbtree wrappers */
int delete_vnode(unsigned int key, rb_node_t* root, rb_node_t* node);
int search_vnode(unsigned int key, rb_node_t* root, rb_node_t* node);
int update_vnode(unsigned int key, char *data, rb_node_t* root);
int add_vnode(pnode *vnode, rb_node_t* root, int vnum);
