#pragma once

#include <queue>
#include <stack>

template<class T>
struct BinaryTreeNode		  //���ڵ�
{
	T _data;	
	BinaryTreeNode<T>* _left;	
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(const T* a, size_t size)
	{
		size_t index = 0;
		_root = _CreateTree(a, size, index);
	}

	~BinaryTree()
	{
		_Destroy(_root);
		_root = NULL;
	}

	BinaryTree(const BinaryTree<T>& t)
	{
		_root = _Copy(t._root);
	}

	BinaryTree<T>& operator=(BinaryTree<T> t)
	{
		swap(_root, t._root);

		return *this;
	}

	void LevelOrder()
	{
		_LevelOrder();
		cout << endl;
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout << endl;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}

	int Size()
	{
		int size = 0;
		_Size(_root, size);
		return size;
	}

	int Depth()
	{
		return _Depth(_root);
	}

	BinaryTreeNode<T>* Find(const T& x)
	{
		return _Find(_root, x);
	}

	bool IsCompleteBinaryTree()
	{
		return _IsCompleteBinaryTree(_root);
	}

	void TreeMirror()
	{
		_TreeMirror(_root);
	}

	void TreeMirror_NonR()
	{
		_TreeMirror_NonR(_root);
	}

//1&2. ������������֮ ��Σ��������򣬺������
	//�������Ĳ�α���
	void _LevelOrder()
	{
		queue<BinaryTreeNode<T>*> q;		//����һ������q
		if (_root)						//�ж�_root�Ƿ�Ϊ��
		{
			q.push(_root);
		}
		while (!q.empty())	
		{
			BinaryTreeNode<T>* front = q.front();
			q.pop();
			cout << front->_data << " ";

			if (front->_left)			//�����������ν�����У��������
			{
				q.push(front->_left);
			}
			
			if (front->_right)
			{
				q.push(front->_right);
			}
		}

		cout << endl;
	}

	////��α�����������������������
	//void _LevelOrderS()
	//{
	//	queue<BinaryTreeNode<T>*> q;
	//	int n = 1;

	//	if (_root)
	//	{
	//		q.push(_root);
	//	}

	//	while (!q.empty())
	//	{
	//		BinaryTreeNode<T>* front = q.front();
	//		q.pop();
	//		cout << front->_data << " ";

	//		if (n == 0)
	//		{
	//			if (front->_left)
	//			{
	//				q.push(front->_left);
	//			}

	//			if (front->_right)
	//			{
	//				q.push(front->_right);
	//			}
	//			n = 1;
	//		}
	//		else
	//		{
	//			if (front->_right)
	//			{
	//				q.push(front->_right);
	//			}

	//			if (front->_left)
	//			{
	//				q.push(front->_left);
	//			}
	//			n = 0;
	//		}
	//	}

	//	cout << endl;
	//}

	//������ǰ�����
	void PrevOrder_NonR()
	{
		stack<BinaryTreeNode<T>*> s;
		if (_root)
		{
			s.push(_root);	//������ջ
		}
		while (!s.empty())  //ջ��Ϊ�գ����ڵ��ȳ�ջ
		{
			BinaryTreeNode<T>* top = s.top();
			s.pop();
			cout << top->_data << " ";


			if (top->_right)			//ѹ��������
			{
				s.push(top->_right);
			}

			if (top->_left)			//ѹ��������
			{
				s.push(top->_left);
			}
		}

		cout << endl;
	}

	void InOrder_NonR()
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = _root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			if (!s.empty())
			{
				BinaryTreeNode<T>* top = s.top();
				cout << top->_data << " ";
				s.pop();

				cur = top->_right;
			}
		}

		cout << endl;
	}

	void PostOrder_NonR()
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = _root;
		BinaryTreeNode<T>* prevVisited = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			BinaryTreeNode<T>* top = s.top();
			if (top->_right == NULL || top->_right == prevVisited)
			{
				cout << top->_data << " ";
				prevVisited = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}

	int GetLeafNum()
	{
		int num = 0;
		_GetLeafNum(_root, num);
		return num;
	}

protected:
	BinaryTreeNode<T>* _Copy(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return NULL;
		}

		BinaryTreeNode<T>* newRoot = new BinaryTreeNode<T>(root->_data);
		newRoot->_left = _Copy(root->_left);
		newRoot->_right = _Copy(root->_right);

		return newRoot;
	}

	void _Destroy(BinaryTreeNode<T>*& root)
	{
		if (root == NULL)
		{
			return;
		}

		if (root->_left == NULL && root->_right == NULL)
		{
			delete root;
			root = NULL;
			return;
		}

		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	BinaryTreeNode<T>* _CreateTree(const T* a, size_t size, size_t& index)
	{
		BinaryTreeNode<T>* root = NULL;
		if (index < size && a[index] != '#')
		{
			root = new BinaryTreeNode<T>(a[index]);
			root->_left = _CreateTree(a, size, ++index);
			root->_right = _CreateTree(a, size, ++index);
		}

		return root;
	}

	void _PrevOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _InOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}

	void _PostOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}

	void _Size(BinaryTreeNode<T>* root, int& size)
	{
		if (root == NULL)
		{
			return;
		}
		else
		{
			size++;
		}
		_Size(root->_left, size);
		_Size(root->_right, size);
	}

//3. ��������������������ĸ߶�
	int _Depth(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int leftDepth = _Depth(root->_left);
		int rightDepth = _Depth(root->_right);

		return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
	}

//6. ������������֮�ж�һ�����ǲ����ڶ�������
	BinaryTreeNode<T>* _Find(BinaryTreeNode<T>* root, const T& x)
	{
		if (root == NULL)
		{
			return NULL;
		}

		else if (root->_data == x)
		{
			return root;
		}
		else
		{
			BinaryTreeNode<T>* ret = _Find(root->_left, x);
			if (ret)
			{
				return ret;
			}
			else
			{
				return _Find(root->_right, x);
			}
		}
	}

//5. ������������֮���������K��Ľ�����
	int _GetLevelLeafNum(const BinaryTreeNode<T>* root, const int k)
	{
		int count = 0;

		if (root == NULL || k < 0)
		{
			return 0;
		}

		if (k == 0)
		{
			count++;
		}

		_GetLevelLeafNum(root->_left, k - 1);
		_GetLevelLeafNum(root->_right, k - 1);
		return count;
	}


//4. ��������������Ҷ�ӽڵ����
	void _GetLeafNum(BinaryTreeNode<T>* root, int& num)
	{
		if (root == NULL)
		{
			return;
		}

		if (root->_left == NULL&&root->_right == NULL)
		{
			++num;
			return;
		}

		_GetLeafNum(root->_left, num);
		_GetLeafNum(root->_right, num);
	}


//8.�ж�ƽ�������--��ƽ���������ļ���


//7. ��������������֮�������ڵ������������Ƚڵ�
	int FindCommonAncestor(BinaryTreeNode<T>* root,BinaryTreeNode<T>* node1, BinaryTreeNode<T>* node2)
	{

	}

//10. ������������֮��ǰ���������������ؽ�������
	//BinaryTreeNode* RebuildBinaryTree(int* pPrevOrder, int* pInOrder, size_t length)
	//{
	//	if (pPrevOrder == NULL || pInOrder == NULL || length <= 0)
	//	{
	//		return NULL;
	//	}

	//	return ConstructCore(pPrevOrder, pPrevOrder + length - 1, pInOrder, pInOrder + length - 1);
	//}

	//BinaryTreeNode* ConstructCore(int* startPrevOrder,  int* startInOrder)
	//{
	//	BinaryTreeNode<T>* newRoot = new BinaryTreeNode<T>();
	//	//ǰ��������еĵ�һ�������Ǹ��ڵ��ֵ
	//	newRoot->_data = startPrevOrder[0];
	//	newRoot->_left = newRoot->_right = NULL;
	//	int i = 0;
	//	while (startInOrder[i] != newRoot->_data)
	//	{
	//		i++;
	//	}
	//	int rootPosInOrder = i;

	//	//�ؽ�������
	//	size_t leftLength = rootPosInOrder;
	//	if (leftLength > 0)
	//	{
	//		newRoot->_left = ConstructCore(startPrevOrder + 1, startInOrder);
	//	}
	//	//�ؽ�������
	//	if (leftLength<)
	//}

//9. ������������֮����������Զ�������ڵ�֮��ľ���
	void MaxDistance()
	{

	}

//11. ������������֮�ж�һ�����ǲ�����ȫ������
	bool _IsCompleteBinaryTree(BinaryTreeNode<T>* root)
	{
		//����Ҳ��������ȫ������
		if (root == NULL)
			return true;

		queue<BinaryTreeNode<T>*> q;
		q.push(root);
		bool NextNoChild = false;
		bool result = true;
		
		while(!q.empty())
		{
			BinaryTreeNode<T>* pNode = q.front();
			q.pop();
			if (NextNoChild)
			{
				if (pNode->_left != NULL || pNode->_right != NULL)
				{
					result = false;
					break;
				}
			}
			else if (pNode->_left != NULL && pNode->_right != NULL)
			{
				q.push(pNode->_left);
				q.push(pNode->_right);
			}
			else if (pNode->_left != NULL && pNode->_right == NULL)
			{
				q.push(pNode->_left);
				NextNoChild = true;
			}
			else if (pNode->_left == NULL && pNode->_right != NULL)
			{
				return false;
				break;
			}
			else
			{
				NextNoChild = true;
			}
		}
		return result;
	}

//12. ������������֮��������ľ���
	//�ݹ�ʵ��
	void _TreeMirror(BinaryTreeNode<T>* root)
	{
		if (root == NULL || (root->_left == NULL && root->_right == NULL))
		{
			return;
		}

		swap(root->_left, root->_right);
		if (root->_left)
			_TreeMirror(root->_left);
		if (root->_right)
			_TreeMirror(root->_right);
	}

	//�ǵݹ�ʵ��
	void _TreeMirror_NonR(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;
		stack<BinaryTreeNode<T> *> s;
		s.push(root);

		while (s.size())
		{
			BinaryTreeNode<T>* pNode = s.top();
			s.pop();

			if (NULL != pNode->_left || NULL != pNode->_right)
			{
				BinaryTreeNode<T> *pTemp = pNode->_left;
				pNode->_left = pNode->_right;
				pNode->_right = pTemp;
				//swap(pNode->_left, pNode->_right);
			}

			if (NULL != pNode->_left)
				s.push(pNode->_left);

			if (NULL != pNode->_right)
				s.push(pNode->_right);
		}
	}

//13. ������������֮������������ת��Ϊһ�������˫������Ҫ���ܴ����κ��µĽ�㣬ֻ�ܵ����������ָ���ָ��
	void ToList()
	{

	}

protected:
	BinaryTreeNode<T>* _root;
};

void TestBinaryTree()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int>t1(a, 10);
	t1.PrevOrder();
	t1.InOrder();
	t1.PostOrder();
	t1.LevelOrder();
	t1._LevelOrderS();
	//cout << "size:" << t1.Size() << endl;
	//cout << "depth:" << t1.Depth() << endl;
	//cout << "IsCompleteBinaryTree: " << t1.IsCompleteBinaryTree() << endl;
	//t1.TreeMirror();
	//t1.LevelOrder();
	//t1.TreeMirror_NonR();
	//t1.LevelOrder();

	//int b[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	//BinaryTree<int>t2(b, 15);
	//t2.PrevOrder();
	//cout << "size:" << t2.Size() << endl;
	//cout << "depth:" << t2.Depth() << endl;

	//cout << t2.Find(8)->_data << endl;
	//cout << t2.Find(6)->_data << endl;

	//t2.PrevOrder();
	//t2.PrevOrder_NonR();

	//t2.InOrder();
	//t2.InOrder_NonR();

	//t2.PostOrder();
	//t2.PostOrder_NonR();

	//cout << "LevelOrder�� ";
	//t2.LevelOrder();

	//cout << "Ҷ�ӽڵ�ĸ�����" << t2.GetLeafNum() << endl;
	//cout << "IsCompleteBinaryTree: " << t2.IsCompleteBinaryTree() << endl;
}







