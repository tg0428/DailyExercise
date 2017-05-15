#pragma once

namespace tg
{
	enum colorType
	{
		RBTREE_RED,
		RBTREE_BLACK
	};

	typedef struct treeNode
	{
		size_t _key;
		colorType _nodeType;
		treeNode * _parent;
		treeNode * _lChild;
		treeNode * _rChild;

		treeNode(const int& value) :_key(value) 
		{
			_parent = nullptr;
			_lChild = nullptr;
			_rChild = nullptr;
		}
	} Node;

	class RBTree
	{
	public:
		RBTree();
		~RBTree();

		void insertNode(const int& value);			// 插入节点
		void findNode(const int& value);			// 查找节点
		void removeNode(const int& value);			// 删除节点

	private:
		void init();								// 初始化红黑树
		void color(Node * node, colorType type_c);	// 设置结点颜色

		Node * makeHead();							// 设置头结点
		Node * createNode(const int& value);		// 创建新节点
		Node * parent(Node* node);					// 获取节点的父节点

		void leftMost(Node* node, Node* child);		// 设置左子节点
		void rightMost(Node* node, Node* child);	// 设置右子节点
		void parentMost(Node* node, Node* parent);	// 设置父节点

		void treeLeftRotate(Node* node);			// 左旋
		void treeRightRotate(Node* node);			// 右旋
		void balanceRBTree(Node* node);				// 平衡化

		bool clrType(Node* node, colorType type);					// 识别节点颜色

	private:
		Node * _Head;
		Node * _Root;
	};
}

//////////////////////////////////////////////////////////////////////////
/**
	note:
	隶属于动态查找范围概念：

	RB-tree : 红黑树， 平衡二叉查找树的一种，标准库STL中，set，map均已红黑树为底层存储数据结构， 本身具有排序功能
		， 且查找元素迅速

	* 与 RB-tree 同级的还有 AVL-tree (Adelson-velskii-landis) 

	RB-tree definition : 
		1. 满足二叉树查找树的所有条件
		2. 所有节点不是黑色就是红色
		3. 根节点为黑色
		4. 如果节点为红色，那么其子节点必须为黑色
		5. 任一节点至nil(黑色)的任何路径，包含的黑色节点数必须相同

	AVL-tree definition :
		1. 满足二叉查找树的所有条件
		2. 每个节点的左右子树高度相差不能超过1

	* 重点：

		平衡化的意义： 使每次查找元素的平均查找长度为O(nlogn)
		二叉查找树平衡化 ： 依照RB-tree 与 AVL-tree的相关性质，当插入不满足红黑树，avl树性质的节点，对树进行平衡化旋转操作
		旋转操作分为 ： 单旋 - 双旋

		平衡被破坏的几种情况： (RB-tree 及 AVL-tree 均使用此方法对平衡被破坏的二叉查找树再平衡化)
		1. 插入节点在X节点的左子节点的左子树上 -- 左左 ---- 单旋 且是 右旋				# 外侧插入
		2. 插入节点在x节点的左子节点的右子树上 -- 左右 ---- 双旋 且是 先左旋 再 右旋		# 内侧插入
		3. 插入节点在x节点的右子节点的左子树上 -- 右左 ---- 双旋 且是 先右旋 再 左旋		# 内侧插入
		4. 插入节点在x节点的右子节点的右子树上 -- 右右 ---- 单旋 且是 左旋				# 外侧插入
*/