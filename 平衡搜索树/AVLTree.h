#pragma once

template<class K, class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;				//ƽ������

	AVLTreeNode(const K& key, const V& value)
		: _key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		: _root(NULL)
	{}

	~AVLTree()
	{}

public:

	//����
	//����λ��
	//����ڵ�
	//����ƽ������
	//�����������ת��������parent������������

	bool Insert(const K& key, const V& value)
	{
		//����
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		//����λ��
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		//����ڵ�
		cur = new Node(key, value);

		if (key > parent->_key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		//����ƽ������(����-����)
		bool isRotate = false;	//�����־λ����¼�Ƿ���ת
		while (parent)
		{
			if (parent->_left == cur)//����parent����ߣ�ƽ�����Ӽ�1
			{
				parent->_bf--;
			}
			else                   //����parent���ұߣ�ƽ�����Ӽ�1
			{
				parent->_bf++;
			}

			if (parent->_bf == 0)
				break;
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else//��ת������ƽ������  2  -2
			{
				isRotate = true;

				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						_RotateL(parent);
					}
					else //cur->_bf == -1
					{
						_RotateRL(parent);
					}
				}
				else  //parent->_bf == -2
				{
					if (cur->_bf == -1)
					{
						_RotateR(parent);
					}
					else
					{
						_RotateLR(parent);
					}
				}
				break;
			}
		}
		if (isRotate) //true���ʾ�����˵���
		{
			Node* GrandParent = parent->_parent;
			if (GrandParent == NULL)
			{
				_root = parent;
			}
			else
			{
				if (parent->_key < GrandParent->_key)
				{
					GrandParent->_left = parent;
				}
				else
				{
					GrandParent->_right = parent;
				}
			}
		}
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool IsBalanceTree()
	{
		return _IsBalanceTree(_root);
	}
protected:

//8. ������������֮ �ж�һ�ö������ǲ���ƽ�������
		bool _IsBalanceTree(Node* root)
		{
			if (root == NULL)
			{
				return true;
			}
			int left = _Height(root->_left);
			int right = _Height(root->_right);

			int bf = abs(right - left);
			if (bf > 1)
			{
				return false;
			}
			else if (bf != abs(root->_bf))
			{
				cout << root->_bf << "ƽ����������" << endl;
				return false;
			}
			return _IsBalanceTree(root->_left) && _IsBalanceTree(root->_right);
		}

	//����
		void _RotateL(Node*& parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			parent->_right = subRL;
			if (subRL)
			{
				subRL->_parent = parent;
			}

			subR->_left = parent;
			subR->_parent = parent->_parent;
			parent->_parent = subR;

			parent->_bf = subR->_bf = 0;

			parent = subR;
		}

		void _RotateR(Node*& parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			parent->_left = subLR;
			if (subLR)
			{
				subLR->_parent = parent;
			}

			subL->_right = parent;
			subL->_parent = parent->_parent;
			parent->_parent = subL;

			parent->_bf = subL->_bf = 0;

			parent = subL;
		}

		void _RotateLR(Node*& parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			// ����
			subL->_right = subLR->_left;
			if (subLR->_left)
			{
				subLR->_left->_parent = subL;
			}

			subLR->_left = subL;
			subLR->_parent = subL->_parent;
			subL->_parent = subLR;

			if (subLR->_bf == 0 || subLR->_bf == -1)
			{
				subL->_bf = 0;
			}
			else // subLR->_bf == 1
			{
				subL->_bf = -1;
			}

			// �ҵ���
			parent->_left = subLR->_right;
			if (subLR->_right)
			{
				subLR->_right->_parent = parent;
			}

			subLR->_right = parent;
			subLR->_parent = parent->_parent;
			parent->_parent = subLR;

			if (subLR->_bf == 0 || subLR->_bf == 1)
			{
				parent->_bf = 0;
			}
			else // subLR->_bf == -1
			{
				parent->_bf = 1;
			}

			subLR->_bf = 0;
			parent = subLR;
		}

		void _RotateRL(Node*& parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			subR->_left = subRL->_right;
			if (subRL->_right)
			{
				subRL->_right->_parent = subR;
			}

			subRL->_right = subR;
			subR->_parent = subRL;

			if (subRL->_bf == 0 || subRL->_bf == 1)
			{
				subR->_bf = 0;
			}
			else
			{
				subR->_bf = 1;
			}

			parent->_right = subRL->_left;
			if (subRL->_left)
			{
				subRL->_left->_parent = parent;
			}

			subRL->_left = parent;
			subRL->_parent = parent->_parent;
			parent->_parent = subRL;

			if (subRL->_bf == 0 || subRL->_bf == -1)
			{
				parent->_bf = 0;
			}
			else
			{
				parent->_bf = -1;
			}

			subRL->_bf = 0;
			parent = subRL;
		}


	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	int _Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		int left = _Height(root->_left) + 1;
		int right = _Height(root->_right) + 1;

		return left > right ? left : right;
	}

protected:
	Node* _root;
};


void TestAVL1()
{
	AVLTree<int, int> t;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		t.Insert(a[i], i);
	}
	t.InOrder();
	cout << "IsBlance?" << t.IsBalanceTree() << endl;
}

void TestAVL2()
{
	AVLTree<int, int> t;
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		t.Insert(a[i], i);
		t.InOrder();
	}
	cout << "IsBlance?" << t.IsBalanceTree() << endl;
}