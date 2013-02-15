/*
* 二叉查找树的左旋操作,该操作要求x的右子树不为空
*/
static void rbTreeLeftRotate(RBTree *rbTree, RBTreeNode *x);
/*
* 二叉查找树的右旋操作,该操作要求x的左子树不为空
*/
static void rbTreeRightRotate(RBTree *rbTree, RBTreeNode *x);

/*
* 当插入一个节点后，用此过程来保持红黑树的性质
*/
static void rbTreeInsertFixup(RBTree *rbTree, RBTreeNode *x);

/*
* 当删除一个结点时，通过此过程保持红黑树的性质
*/
static void rbTreeDeleteFixup(RBTree *rbTree, RBTreeNode *parent, RBTreeNode *x);

//插入操作
//1. 新创建的结点，颜色为红色
//2. 插入一个结点后，有可能破坏红黑树的性质，则必须对树作相应的调整，以便保持红黑树的性质
BOOL rbInsertNode(RBTree *rbTree, data_t data) {
	//1. 创建一个新结点
	RBTreeNode *node, *p, *curNode;

	node = (RBTreeNode *)malloc(sizeof(RBTreeNode));
	if (node == NULL) return FALSE;
	node->data = data;
	node->color = RED;
	node->left = NULL;
	node->right = NULL;

	curNode = *rbTree;
	//找到新结点的插入位置, p保存着待插入结点的父结点
	p = NULL;
	while (curNode != NULL) {
		p = curNode;
		if (data < curNode->data) {
			curNode = curNode->left;
		} else {
			curNode = curNode->right;
		}
	}
	//空树
	if (p == NULL) {
		*rbTree = node;
	} else {
		if (data < p->data) {
			p->left = node;
		} else {
			p->right = node;
		}
	}
	node->parent = p;
	//关键：调整红黑树，以保持性质
	rbTreeInsertFixup(rbTree, node);
	return TRUE;
}

BOOL rbDeleteNode(RBTree *rbTree, data_t data) {
	RBTreeNode *target, *realDel, *child;
	
	target = rbSearch(rbTree, data);
	if (target != NULL) {
		//找到待删除的真正结点位置
		if (target->left == NULL || target->right == NULL) {
			realDel = target;
		} else {
			realDel = rbSuccessor(target);
		}
		//将待删除节点的子树链接到其父节点上，待删除的节点最多只有一个子树
		if (realDel->left != NULL) {
			child = realDel->left;
		} else {
			child = realDel->right;
		}

		if (child != NULL) {
			child->parent = realDel->parent;
		} 

		if (realDel->parent == NULL) {
			*rbTree = child;
		} else {
			if (realDel->parent->left == realDel) {
				realDel->parent->left = child;
			} else {
				realDel->parent->right = child;
			}
		}

		if (target != realDel) {
			target->data = realDel->data;
		}

		//删除的重新结点是黑色的才需要调整
		if (realDel->color == BLACK) {
			rbTreeDeleteFixup(rbTree, realDel->parent, child);
		}
		free(realDel);
		return TRUE;
	} else {
		return FALSE;
	}
}
/*
* 插入一个结点时。可能被破坏的性质为（4）如果一个结点是红色的，则它的孩子结点是黑色的
* （2）根结点是黑色的
*/
static void rbTreeInsertFixup(RBTree *rbTree, RBTreeNode *x) {
	RBTreeNode *p, *gparent, *uncle;

	//纠正性质2
	while ((p = x->parent) != NULL && p->color == RED){
		gparent = p->parent;
		//如果父结点是祖父结点的左孩子（因为父结点是红色结点，所以肯定有祖父结点）
		if (p == gparent->left) {
			uncle = gparent->right;
			//情况1：如果存在叔父结点，并且叔父结点颜色为红色，则可以通过改变祖父，父亲和叔父结点的颜色
			//使得当前存在破坏性质的结点沿树上升，由x变为其祖父
			if (uncle != NULL && uncle->color == RED) {
				gparent->color = RED;
				p->color = BLACK;
				uncle->color = BLACK;
				x = gparent;
			} 
			//叔父不存在或者存在但是颜色是黑色的，则必须通过寻转来配合改变颜色来保持性质2
			else {
				// 情况2：x为其父结点的右孩子，通过左旋转换为情况3
				if (x == p->right) {
					//基于x的父结点做左旋，记原x结点位x‘
					x = p;
					rbTreeLeftRotate(rbTree, x);
					//旋转后，重置x，使其仍未x节点的父结点（也即x’）
					p = x->parent;
				}
				//情况三：x为其父结点的左孩子，调整父结点和祖父结点的颜色，以纠正性质4，但是破坏了性质5
				p->color = BLACK;
				gparent->color = RED;
				//基于祖父结点右旋以保持性质5
				rbTreeRightRotate(rbTree, gparent);
				//此时x->parent->color = BLACK, 循环结束
			}
		} 
		// 父结点是祖父结点的右孩子
		else {
			uncle = gparent->left;
			//情况1：如果存在叔父结点，并且叔父结点颜色为红色，则可以通过改变祖父，父亲和叔父结点的颜色
			//使得当前存在破坏性质的结点沿树上升，由x变为其祖父
			if (uncle != NULL && uncle->color == RED) {
				gparent->color = RED;
				p->color = BLACK;
				uncle->color = BLACK;
				x = gparent;
			} 
			//情况2和情况3
			else {
				// 情况2：x为其父结点的左孩子，通过旋转换为右情况3
				if (x == p->left) {
					x = p;
					rbTreeRightRotate(rbTree, x);
					p = x->parent;
				}
				//情况三：x为其父结点的左孩子，调整父结点和祖父结点的颜色，以纠正性质4，但是破坏了性质5
				p->color = BLACK;
				gparent->color = RED;
				//基于祖父结点左旋以保持性质5
				rbTreeLeftRotate(rbTree, gparent);
				//此时x->parent->color = BLACK, 循环结束
			}
		}
	}
	//保持性质2
	(*rbTree)->color = BLACK;
}

/*
* 删除一个黑结点会导致如下三个问题： 
* （1）如果被删除结点y是根结点，而y的一个红色孩子成为了新的根，则违反了性质2
* （2）如何y的父结点和其孩子结点都是红色的，则违反了性质4
* （3）删除y将导致先前包含y的任何路径上的黑结点树少一个，破坏了性质5。
* 解决方案是：被删除的结点黑色属性下移到其孩子结点x上。此时性质5都得以保持，于是存在2种情况：
* （1）x原来为红色，此时孩子结点属性是红黑，此时破坏了性质（1），（4），如果x还是树根则，破坏了性质（2）
*		处理方式为：将x重新着色为黑色（此操作同时去除其多余的黑色属性），处理完毕，红黑树性质得以保持
* （2）x原来为黑色，此时x的属性为双重黑色，破坏了性质（1），若x为树根，则可以只是简单的消除x多余的黑色属性
*		否则需要做必要的旋转和颜色修改
*/
static void rbTreeDeleteFixup(RBTree *rbTree, RBTreeNode *parent, RBTreeNode *x) {
	RBTreeNode *brother;

	while ((x == NULL || x->color == BLACK) && x != *rbTree) {
		if (x == parent->left) {
			brother = parent->right;
			//因为被删除结点为黑色，其必然有兄弟结点,也即是现在x的兄弟结点（由性质5保证）
			//情况1：如果兄弟结点为红色,则parent颜色比为黑色，此时调整颜色，并左旋，使得brother和
			//parent位置调换，此操作不破坏别的性质，并将情况1变化为情况2，3，4
			if (brother->color == RED) {
				brother->color = BLACK;
				parent->color = RED;
				//左旋调整brother和parent的位置
				rbTreeLeftRotate(rbTree, parent);
				//重置brother，转换到情况2，3，4
				brother = parent->right; //此时brohter颜色肯定为黑色，并且不为NULL
			}
			//情况2： brother有两个黑色结点（NULL也为黑色结点）:将x和brother抹除一重黑色
			//具体操作为，brother的颜色变为红，x结点上移到其父结点
			if ((brother->left == NULL || brother->left->color == BLACK) && 
				(brother->right == NULL || brother->right->color == BLACK)) {
					brother->color = RED;
					x = parent;
					parent = parent->parent;
			} else {
				//情况3： brother左孩子为红色结点，右孩子为黑色结点
				if (brother->right == NULL || brother->color == BLACK) {
					brother->left->color = BLACK;
					brother->color = RED;
					//右旋使情况3变化为情况4
					rbTreeRightRotate(rbTree, brother);
					//重置brother
					brother = parent->right;
				}
				//情况4：brother的右孩子为红色结点:
				//交换brother和parent的颜色和位置，使得x的2重黑色属性中的一重转移到其parent上
				//此时到brother的右孩子的黑结点数少一，于是将右结点的颜色置黑，红黑树性质得以保持
				brother->color = parent->color;
				parent->color = BLACK;
				brother->right->color = BLACK;
				rbTreeLeftRotate(rbTree, parent);
				
				//至x为树根，结束循环
				x = *rbTree;
			}
		} 
		else {
			brother = parent->left;
			//情况1
			if (brother->color == RED) {
				brother->color = BLACK;
				parent->color = RED;
				rbTreeRightRotate(rbTree, parent);
				brother = parent->left;
			}
			//情况2
			if ((brother->left == NULL || brother->left->color == BLACK) && 
				(brother->right == NULL || brother->right->color == BLACK)) {
					brother->color = RED;
					x = parent;
					parent = parent->parent;
			} else {
				//情况3：： brother右孩子为红色结点，左孩子为黑色结点
				if (brother->left  == NULL || brother->left->color == BLACK) {
					brother->right->color = BLACK;
					brother->color = RED;
					rbTreeLeftRotate(rbTree, brother);
					//重置brother
					brother = parent->left;
				}
				//情况4： brother的左孩子为红色结点
				brother->color = parent->color;
				parent->color = BLACK;
				brother->left->color = BLACK;
				rbTreeRightRotate(rbTree, parent);

				x = *rbTree; 
			}
		}
	}
	if (x != NULL) {
		x->color = BLACK;
	}
}

static void rbTreeLeftRotate(RBTree *rbTree, RBTreeNode *x) {
	RBTreeNode *y;

	y = x->right;
	x->right = y->left;
	if (y->left != NULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	//x为树根
	if (x->parent == NULL) {
		*rbTree = y;
	} else {
		if (x->parent->left == x) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
	}
	y->left = x;
	x->parent = y;
}
static void rbTreeRightRotate(RBTree *rbTree, RBTreeNode *x) {
	RBTreeNode *y;

	y = x->left;

	x->left = y->right;
	if (y->right != NULL) {
		y->right->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == NULL) {
		*rbTree = y;
	} else {
		if (x->parent->left == x) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
	}

	y->right = x;
	x->parent = y;
}

