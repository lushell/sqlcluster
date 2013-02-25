#include "rbtree.h"
<<<<<<< HEAD
#include "md5hash.h"
/* Entity node, storage in array */
typedef struct _pnode {
	unsigned int id;
	char	ipv4[14];	/* Compatible ipv4 */
=======
/* Virtual node number */
#define vns	4
/* Entity node, storage in array */
typedef struct _pnode {
	unsigned int id;
	hash_key vkey[vns];
	char	ipv4[32];	/* Compatible ipv4 */
>>>>>>> 6db37952fadc9ab313299bfc85fbd431eef46c10
//	char ipv6[31];		/* Compatible ipv6 */
} pnode;

/* Max server = nodes + vnum_max */
#define nodes	0
<<<<<<< HEAD
#define vnum_max	4	/* Eentity node mapping to virtual node */
#define max_nodes	0xfff	/* Max node */
=======
#define vns	4
>>>>>>> 6db37952fadc9ab313299bfc85fbd431eef46c10

/* Rbtree wrappers */
int delete_vnode(unsigned int key, rb_node_t* root, rb_node_t* node);
int search_vnode(unsigned int key, rb_node_t* root, rb_node_t* node);
int update_vnode(unsigned int key, char *data, rb_node_t* root);
<<<<<<< HEAD
int add_vnode(pnode *vnode, rb_node_t* root, int vnum);
=======
int add_vnode(rb_node_t* root, pnode *mac_node);

int generate_vkey(pnode *mac_node);
>>>>>>> 6db37952fadc9ab313299bfc85fbd431eef46c10
