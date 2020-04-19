/**************************************************************************
�ѣ���С�ѵķ�ʽ����������
**************************************************************************/
#pragma once
#include <vector>
#include <cassert>


template<class T, class Compare>
class Heap
{
public:
	Heap()
	{}

	Heap(const T* array, size_t size)
	{
		assert(array);

		for (int i = 0; i< size; ++i)
		{
			_array.push_back(array[i]);
		}

		for (int i = _array.size() / 2 - 1; i >= 0; --i)
		{
			_AdjustDown(_array, i, _array.size());
		}
	}

	Heap(const vector<T>& vec)
	{
		_array.swap(vec);

		for (int i = _array.size() / 2 - 1; i >= 0; --i)
		{
			_AdjustDown(_array, i, _array.size());
		}
	}

	// ����һ������x����С����
	void Push(const T& x)
	{
		_array.push_back(x);

		if (_array.size() > 1)
		{
			_AdjustUp(_array, _array.size() - 1);
		}
	}

	// ɾ���Ѷ�Ԫ��
	void Pop()
	{
		int size = _array.size();
		assert(size > 0);

		swap(_array[0], _array[size - 1]);
		_array.pop_back();

		if (_array.size() > 1)
		{
			_AdjustDown(_array, 0, _array.size());
		}
	}

	const T& Top()
	{
		return _array[0];
	}

/**************************************************************************
�������ƣ�_AdjustDown
����������vector<T>& vec		vector<T>ʵ������
		 int root			���ڵ㣨�������±��ֵ��
		 int size			ʵ����С���������С��
����ֵ���ͣ�void
�������ܣ������ڵ����µ�����С�Ѿ�����
**************************************************************************/
	void _AdjustDown(vector<T>& vec, int root, int size)
	{
		// 1.childָ�����ӽڵ�
		int child = root * 2 + 1;
		while (child < size)
		{
			// 2.childָ�����Һ�����С�Ľڵ�
			if (child + 1 < size && Compare()(vec[child + 1], vec[child]))
			//if (child + 1 < size && vec[child+1] < vec[child])
			{
				++child;
			}

			// 3.��childС�ڸ��ڵ㣬�򽻻�child��root�ڵ㣬���������µ���
			if (Compare()(vec[child], vec[root]))
				//if (vec[child] < vec[root])
			{
				swap(vec[child], vec[root]);
				root = child;
				child = root * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

/**************************************************************************
�������ƣ�_AdjustUp
����������vector<T>& vec		vector<T> ʵ��������
		 int pos				�������һ��ֵ���±�
����ֵ���ͣ�void
�������ܣ�һ���ڵ����ϵ�����С�Ѿ���˵����
**************************************************************************/
	void _AdjustUp(vector<T>& vec, int pos)
	{
		// 1.parentָ�򸸽ڵ�
		int child = pos;
		int parent = (child - 1) / 2;

		// ��child==0ʱ�����ϵ���ɡ�����ʹ��parent���жϣ�parent����С��0
		//while(parent >= 0)
		while (child > 0)
		{
			// 2.��childС�ڸ��ڵ㣬�򽻻����ӽڵ㣬���������ϵ�����ֱ�����ڵ�
			if (Compare()(vec[child], vec[parent]))
			//if (vec[child] < vec[parent])
			{
				swap(vec[child], vec[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	// �ж��Ƿ�Ϊ��
	bool Empty()
	{
		return _array.empty();
	}

	size_t Size()
	{
		return _array.size();
	}

private:
	vector<T> _array;
};