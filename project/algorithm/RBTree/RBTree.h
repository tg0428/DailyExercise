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

		void insertNode(const int& value);			// ����ڵ�
		void findNode(const int& value);			// ���ҽڵ�
		void removeNode(const int& value);			// ɾ���ڵ�

	private:
		void init();								// ��ʼ�������
		void color(Node * node, colorType type_c);	// ���ý����ɫ

		Node * makeHead();							// ����ͷ���
		Node * createNode(const int& value);		// �����½ڵ�
		Node * parent(Node* node);					// ��ȡ�ڵ�ĸ��ڵ�

		void leftMost(Node* node, Node* child);		// �������ӽڵ�
		void rightMost(Node* node, Node* child);	// �������ӽڵ�
		void parentMost(Node* node, Node* parent);	// ���ø��ڵ�

		void treeLeftRotate(Node* node);			// ����
		void treeRightRotate(Node* node);			// ����
		void balanceRBTree(Node* node);				// ƽ�⻯

		bool clrType(Node* node, colorType type);					// ʶ��ڵ���ɫ

	private:
		Node * _Head;
		Node * _Root;
	};
}

//////////////////////////////////////////////////////////////////////////
/**
	note:
	�����ڶ�̬���ҷ�Χ���

	RB-tree : ������� ƽ������������һ�֣���׼��STL�У�set��map���Ѻ����Ϊ�ײ�洢���ݽṹ�� �������������
		�� �Ҳ���Ԫ��Ѹ��

	* �� RB-tree ͬ���Ļ��� AVL-tree (Adelson-velskii-landis) 

	RB-tree definition : 
		1. �������������������������
		2. ���нڵ㲻�Ǻ�ɫ���Ǻ�ɫ
		3. ���ڵ�Ϊ��ɫ
		4. ����ڵ�Ϊ��ɫ����ô���ӽڵ����Ϊ��ɫ
		5. ��һ�ڵ���nil(��ɫ)���κ�·���������ĺ�ɫ�ڵ���������ͬ

	AVL-tree definition :
		1. ����������������������
		2. ÿ���ڵ�����������߶����ܳ���1

	* �ص㣺

		ƽ�⻯�����壺 ʹÿ�β���Ԫ�ص�ƽ�����ҳ���ΪO(nlogn)
		���������ƽ�⻯ �� ����RB-tree �� AVL-tree��������ʣ������벻����������avl�����ʵĽڵ㣬��������ƽ�⻯��ת����
		��ת������Ϊ �� ���� - ˫��

		ƽ�ⱻ�ƻ��ļ�������� (RB-tree �� AVL-tree ��ʹ�ô˷�����ƽ�ⱻ�ƻ��Ķ����������ƽ�⻯)
		1. ����ڵ���X�ڵ�����ӽڵ���������� -- ���� ---- ���� ���� ����				# ������
		2. ����ڵ���x�ڵ�����ӽڵ���������� -- ���� ---- ˫�� ���� ������ �� ����		# �ڲ����
		3. ����ڵ���x�ڵ�����ӽڵ���������� -- ���� ---- ˫�� ���� ������ �� ����		# �ڲ����
		4. ����ڵ���x�ڵ�����ӽڵ���������� -- ���� ---- ���� ���� ����				# ������
*/