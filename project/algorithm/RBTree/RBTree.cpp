#include "RBTree.h"

namespace tg
{
	RBTree::RBTree()
	{
		// ����ͷ��㣬�����ӽ���ָ���Լ���������root��head��root��Ϊ���ڵ�
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
			// head �� root��Ϊ���ڵ�
			parentMost(_Root, _Head);
			parentMost(_Head, _Root);
			color(_Root, RBTREE_BLACK);
		}

		Node * ptr = _Root;
		while (ptr && node_n != _Root)
		{
			// �ж��½ڵ��ֵ�븸�ڵ�ֵ�Ĵ�С��ϵ
			if (node_n->_key >= ptr->_key)
			{
				if (ptr->_rChild == nullptr)
				{
					rightMost(ptr, node_n);		// ��λ
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
					leftMost(ptr, node_n);		// ��λ
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

		// inti left child, point to self . right child is self (����ܳ���ѭ�����õ����⣿������)
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

		// nodeΪ��ƽ��ڵ�
		rightMost(node, node_store_rchild->_lChild);
		parentMost(node_store_rchild->_lChild, node);

		leftMost(node_store_rchild, node);

		if (node->_parent != nullptr)
			parentMost(node_store_rchild, node->_parent);

		// �ж�ԭʼ���ڵ��Ƿ���head
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

		// nodeΪ��ƽ��Ľڵ�
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
		// �ҵ���ƽ��Ľڵ�

		Node * parentPtr;
		
		auto judgeHasParentAndClrType = [&](Node* node_lambda)->bool {
			parentPtr = parent(node_lambda);
			return clrType(parentPtr, RBTREE_RED);
		};

		// ����ڵ�ĸ��ڵ���Ϊ��ɫ��ֱ�Ӳ��룬��ɫ���������ж�
		while (judgeHasParentAndClrType(node))
		{
			Node * gp = parent(parentPtr);
			Node * unclePtr;
			// �ֲ���ڵ��ڸ��ڵ��������������������
			if (gp && gp->_lChild == parentPtr)
			{
				unclePtr = gp->_rChild;
				if (unclePtr == nullptr || clrType(unclePtr, RBTREE_BLACK))		// ���ڵ�Ϊ��ɫ���常�ڵ�Ϊ��ɫ���游�ڵ�Ϊ��ɫ
				{
					if (parentPtr->_lChild == node)
					{
						// ����
						treeRightRotate(gp);
						color(node, RBTREE_BLACK);
					}
					else
					{
						// ˫��ת
						treeLeftRotate(parentPtr);
						treeRightRotate(gp);

						color(node, RBTREE_BLACK);
						color(gp, RBTREE_RED);
					}
					break;
				}
				else if (clrType(unclePtr, RBTREE_RED))		// ���ڵ㣬�常�ڵ��Ϊ��ɫ���游�ڵ�Ϊ��ɫ
				{
					// �ı丸�ڵ㣬�常�ڵ����ɫΪ��ɫ���游�ڵ�Ϊ��ɫ�������游�ڵ㵱���²���Ľڵ���д���
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
				if (unclePtr == nullptr || clrType(unclePtr, RBTREE_BLACK))		// ���ڵ�Ϊ��ɫ���常�ڵ�Ϊ��ɫ���游�ڵ�Ϊ��ɫ
				{
					if (parentPtr->_lChild == node)
					{
						// ˫��
						treeRightRotate(parentPtr);
						treeLeftRotate(gp);
						color(node, RBTREE_BLACK);
						color(gp, RBTREE_RED);
					}
					else
					{
						// ����
						treeLeftRotate(gp);
						color(parentPtr, RBTREE_BLACK);
						color(gp, RBTREE_RED);
					}
					break;
				}
				else if (clrType(unclePtr, RBTREE_RED))		// ���ڵ㣬�常�ڵ��Ϊ��ɫ���游�ڵ�Ϊ��ɫ
				{
					// �ı丸�ڵ㣬�常�ڵ����ɫΪ��ɫ���游�ڵ�Ϊ��ɫ�������游�ڵ㵱���²���Ľڵ���д���
					node = gp;
					color(parentPtr, RBTREE_BLACK);
					color(unclePtr, RBTREE_BLACK);
					color(gp, RBTREE_RED);
					continue;
				}
			}
			else  // gp node is nullptr, parent node is root
			{
				// �����ܣ����ڵ�Ϊ��ɫ
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