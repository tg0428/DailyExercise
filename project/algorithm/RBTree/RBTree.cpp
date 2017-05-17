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
		traversalTree(INORDER, free_node);
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
		while (ptr && node_n != _Root)
		{
			// 判断新节点的值与父节点值的大小关系
			if (node_n->_key >= ptr->_key)
			{
				if (ptr->_rChild == nullptr)
				{
					rightMost(ptr, node_n);		// 就位
					parentMost(node_n, ptr);
					color(node_n, RBTREE_RED);
					break;
				}
				ptr = ptr->_rChild;
			}
			else if (node_n->_key < ptr->_key)
			{
				if (ptr->_lChild == nullptr)
				{
					leftMost(ptr, node_n);		// 就位
					parentMost(node_n, ptr);
					color(node_n, RBTREE_RED);
					break;
				}
				ptr = ptr->_lChild;
			}
		}

		++_Tree_Size;

		// balance
		balanceRBTree(node_n);
	}

	void RBTree::findNode(const int& value)
	{
		Node* node = _Root;
		while (node)
		{
			if (value == node->_key)
			{
				printf("ret : %s", node->to_string().c_str());
				return;
			}

			if (value > node->_key)
			{
				node = node->_rChild;
			}
			else
			{
				node = node->_lChild;
			}
		}
	}

	void RBTree::removeNode(const int& value)
	{
		// TODO
	}

	std::string RBTree::to_string()
	{
		traversalTree(INORDER, nullptr);
		return _SS.str();
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
			parentMost(_Head, node_store_rchild);
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
			return clrType(parentPtr, RBTREE_RED);
		};

		// 插入节点的父节点若为黑色就直接插入，红色进行特殊判断
		while (judgeHasParentAndClrType(node))
		{
			Node * gp = parent(parentPtr);
			Node * unclePtr;
			// 分插入节点在父节点的左子树还是右子树上
			if (gp && gp->_lChild == parentPtr)
			{
				unclePtr = gp->_rChild;
				if (unclePtr == nullptr || clrType(unclePtr, RBTREE_BLACK))		// 父节点为红色，叔父节点为黑色，祖父节点为黑色
				{
					if (parentPtr->_lChild == node)
					{
						// 单旋
						treeRightRotate(gp);
						color(node, RBTREE_BLACK);
					}
					else
					{
						// 双旋转
						treeLeftRotate(parentPtr);
						treeRightRotate(gp);

						color(node, RBTREE_BLACK);
						color(gp, RBTREE_RED);
					}
					break;
				}
				else if (clrType(unclePtr, RBTREE_RED))		// 父节点，叔父节点均为红色，祖父节点为黑色
				{
					// 改变父节点，叔父节点的颜色为黑色，祖父节点为红色，并将祖父节点当做新插入的节点进行处理
					node = gp;
					color(parentPtr, RBTREE_BLACK);
					color(unclePtr, RBTREE_BLACK);
					color(gp, RBTREE_RED);
					continue;
				}
			}
			else if (gp && gp->_rChild == parentPtr)
			{
				unclePtr = gp->_lChild;
				if (unclePtr == nullptr || clrType(unclePtr, RBTREE_BLACK))		// 父节点为红色，叔父节点为黑色，祖父节点为黑色
				{
					if (parentPtr->_lChild == node)
					{
						// 双旋
						treeRightRotate(parentPtr);
						treeLeftRotate(gp);
						color(node, RBTREE_BLACK);
						color(gp, RBTREE_RED);
					}
					else
					{
						// 单旋
						treeLeftRotate(gp);
						color(parentPtr, RBTREE_BLACK);
						color(gp, RBTREE_RED);
					}
					break;
				}
				else if (clrType(unclePtr, RBTREE_RED))		// 父节点，叔父节点均为红色，祖父节点为黑色
				{
					// 改变父节点，叔父节点的颜色为黑色，祖父节点为红色，并将祖父节点当做新插入的节点进行处理
					node = gp;
					color(parentPtr, RBTREE_BLACK);
					color(unclePtr, RBTREE_BLACK);
					color(gp, RBTREE_RED);
					continue;
				}
			}
			else  // gp node is nullptr, parent node is root
			{
				// 不可能，根节点为黑色
			}
		}

		color(_Root, RBTREE_BLACK);
	}

	bool RBTree::clrType(Node* node, colorType type)
	{
		return (node && node->_nodeType == type) ? true : false;
	}

	void RBTree::traversalTree(traversalModel type, __process func)
	{
		switch (type)
		{
		case PREORDER:
			preorderTraversal(_Root);
			break;
		case INORDER:
			inorderTraversal(_Root, func);
			break;
		case POSTORDER:
			postorderTraversal(_Root);
			break;
		default:
			break;
		}
	}

	void RBTree::preorderTraversal(Node * node)
	{
		if (node != nullptr)
		{
			_SS << node->to_string() << "\r\n";
			preorderTraversal(node->_lChild);
			preorderTraversal(node->_rChild);
		}
	}

	void RBTree::inorderTraversal(Node * node, __process func)
	{
		if (node != nullptr)
		{
			inorderTraversal(node->_lChild);
			_SS << node->to_string() << "\r\n";
			inorderTraversal(node->_rChild);
		}
	}

	void RBTree::postorderTraversal(Node * node)
	{
		if (node != nullptr)
		{
			postorderTraversal(node->_lChild);
			postorderTraversal(node->_rChild);
			_SS << node->to_string() << "\r\n";
		}
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
			if (node->_parent->_parent == node)
				return nullptr;
			else
				return node->_parent;
		}
		return nullptr;
	}
}