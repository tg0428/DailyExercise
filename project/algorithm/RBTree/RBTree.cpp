#include "RBTree.h"

namespace tg
{
	RBTree::RBTree()
	{
		// 创建头结点，左右子结点均指向自己，当插入root后，head和root互为父节点
		init();
	}

	RBTree::~RBTree()
	{
	}

	void RBTree::insertNode(const int& value)
	{
		Node * node_n = createNode(value);

		if (_Head->_parent == nullptr)
		{
			_Root = node_n;
			// head 与 root互为父节点
			parentMost(_Root, _Head);
			parentMost(_Head, _Root);
			color(_Root, RBTREE_BLACK);
		}

		Node * ptr = _Root;
		while (ptr)
		{
			// 判断新节点的值与父节点值的大小关系
			if (node_n->_key >= ptr->_key)
			{
				if (ptr->_rChild == nullptr)
				{
					ptr->_rChild = node_n;		// 就位
					color(node_n, RBTREE_RED);
				}
				ptr = ptr->_rChild;
			}
			else if (node_n->_key < ptr->_key)
			{
				if (ptr->_lChild == nullptr)
				{
					ptr->_lChild = node_n;		// 就位
					color(node_n, RBTREE_RED);
				}
				ptr = ptr->_lChild;
			}
		}

		// balance
		balanceRBTree(_Root);
	}

	void RBTree::findNode(const int& value)
	{
		// TODO
	}

	void RBTree::removeNode(const int& value)
	{
		// TODO
	}

	void RBTree::init()
	{
		makeHead();
	}

	Node * RBTree::makeHead()
	{
		_Head = createNode(0);

		// inti left child, point to self . right child is self (这可能出现循环引用的问题？？？？)
		leftMost(_Head, _Head);
		rightMost(_Head, _Head);

		// init head color red
		color(_Head, RBTREE_RED);

		return _Head;
	}

	void RBTree::leftMost(Node * node, Node* child)
	{
		if (node != nullptr)
			node->_lChild = child;
	}

	void RBTree::rightMost(Node * node, Node* child)
	{
		if (node != nullptr)
			node->_rChild = child;
	}

	void RBTree::parentMost(Node * node, Node* parent)
	{
		if (node != nullptr)
			node->_parent = parent;
	}

	void RBTree::treeLeftRotate(Node * node)
	{
		Node * node_store_rchild = node->_rChild;

		// node为非平衡节点
		rightMost(node, node_store_rchild->_lChild);
		parentMost(node_store_rchild->_lChild, node);

		leftMost(node_store_rchild, node);

		if (node->_parent != nullptr)
			parentMost(node_store_rchild, node->_parent);

		// 判断原始父节点是否是head
		if (node->_parent->_parent == node)		// head
		{
			_Root = node_store_rchild;
			parentMost(_Head, node_store_rchild)
		}
		else
		{
			if (node->_parent->_lChild == node)
			{
				leftMost(node->_parent, node_store_rchild);
			}
			else
			{
				rightMost(node->_parent, node_store_rchild);
			}
		}

		parentMost(node, node_store_rchild);
	}

	void RBTree::treeRightRotate(Node * node)
	{
		Node * node_store_left = node->_lChild;

		// node为不平衡的节点
		leftMost(node, node_store_left->_rChild);
		parentMost(node_store_left->_rChild, node);

		rightMost(node_store_left, node);
		if (node->_parent != nullptr)
			parentMost(node_store_left, node->_parent);

		if (node->_parent->_parent == node)		// head
		{
			_Root = node_store_left;
			parentMost(_Head, node_store_left);
		}
		else
		{
			if (node->_parent->_lChild == node)
			{
				leftMost(node->_parent, node_store_left);
			}
			else
			{
				rightMost(node->_parent, node_store_left);
			}
		}

		parentMost(node, node_store_left);
	}

	void RBTree::balanceRBTree(Node * node)
	{
		// 找到不平衡的节点

		Node * parentPtr;
		
		auto judgeHasParentAndClrType = [&](Node* node_lambda)->bool {
			parentPtr = parent(node_lambda);
			return clrType(parentPtr, RBTREE_BLACK);
		};

		while (judgeHasParentAndClrType(node))
		{
			Node * gp = parent(parentPtr);
			// 判断插入的节点是在父节点的左子树的左节点还是右节点 (即 左左 or 左右)
			if (gp && gp->_lChild == parentPtr)
			{
				// 判断插入节点的叔叔节点颜色是否为黑色
				Node * unclePtr = gp->_rChild;
				if (clrType(unclePtr, RBTREE_BLACK))
				{

				}
				else
				{

				}
			}
			// 判断插入的节点是在父节点的右子树的左节点还是右节点 (即 右右 or 右左)
			else
			{

			}
		}
	}

	bool RBTree::clrType(Node* node, colorType type)
	{
		return (node && node->_nodeType == type) ? true : false;
	}

	void RBTree::color(Node * node, colorType type_c)
	{
		if (node != nullptr)
			node->_nodeType = type_c;
	}

	Node * RBTree::createNode(const int & value)
	{
		Node * node_n = new Node(value);
		return node_n;
	}
	Node * RBTree::parent(Node * node)
	{
		if (node->_parent != nullptr)
		{
			if (node->_parent->_parent = node)
				return nullptr;
			else
				return node->_parent;
		}
		return nullptr;
	}
}