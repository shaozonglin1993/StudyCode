/***************************************************************
**	Copyright(c) 2019 VisionMC
**	File Name: template.cpp
**	Auther: Zonglin Shao  Version: 1.0  Data: 2019-5-15
**	Description: 
**			template
**	History:null
***************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "template.h"

bool IsEqual(int left, int right)
{
	return left == right;
}

bool IsEqual(const std::string& left, const std::string& right)
{
	return left == right;
}

void test1(void)
{
	std::string s1("s1"),s2("s2");
	std::cout<<IsEqual(s1,s2)<<std::endl;
	std::cout<<IsEqual(1,1)<<std::endl;
}

//ģ���βεĶ���ȿ���ʹ��class��Ҳ����ʹ��typename����������ͬ��
//template <class �β���1, class �β���2, class �β���n>
//�������� ������(�����б�)
//{...}

template<typename T>
bool _IsEqual(const T& left, const T& right)
{
	return left == right;
}

void test2(void)
{
	std::string s1("s1"),s2("s2");
	std::cout<<_IsEqual(s1,s2)<<std::endl;
	std::cout<<_IsEqual(1,1)<<std::endl;
}

/*ģ�����ƥ�估��ʾʵ����*/
void test3(void)
{
	std::string s1("s1"),s2("s2");
	std::cout<<_IsEqual<std::string>(s1,s2)<<std::endl;
	std::cout<<_IsEqual<int>(1,1)<<std::endl;
}

/*overload template function*/
template<class T1, class T2>
bool _IsEqual(const T1& left, const T2& right)
{
	return left == right;
}


//template<class �β���1, class �β���2, ...class �β���n>
//class ����
//{ ... };

typedef int DataType;
class SeqList
{
public:
	SeqList();
	~SeqList();
private:
	DataType* data;
	int _size;
	int _capacity;
};

template<typename T>
class _SeqList
{
public:
	_SeqList();
	~_SeqList();
private:
	int _size;
	int _capacity;
	T* data;
};

/*��̬˳���*/
template<typename T>
_SeqList<T>::_SeqList()
	:_size(0)
	,_capacity(10)
	,data(new T[_capacity])
{}

template<typename T>
_SeqList<T>::~_SeqList()
{
	delete[] data;
}

void test4(void)
{
	_SeqList<int> s11;
	_SeqList<double> s22;
}

template<class T, class Container = _SeqList<T>>
	class Stack
	{
	public:
		void Push(const T& x);
		void Pop();
		const T& Top();
		bool Empty();
	private:
		Container _con;
	};

void test5(void)
{
	Stack<int> s1;
	Stack<int, _SeqList<int>> s2;
	Stack<int, _SeqList<char>> s3;
}

template<class T, template<class> class Container=_SeqList>
class _Stack
{
public:
	void Push(const T& x);
	void Pop();
	const T& Top();
	bool Empty();
private:
	Container<T> _con;
};

void test6(void)
{
	_Stack<int> s1;
	_Stack<int , _SeqList> s2;
}

/*����������ʹ��*/
void test9(void)
{
	std::vector<int> v;
	for (int i=0; i<10; i++)
    {
		v.push_back(i);
	}
    std::cout <<"���Vector������"<<std::endl;
	for(std::vector<int>::iterator it = v.begin();it != v.end(); it++)
	{
		std::cout<<*it<<" ";
	}
	std::cout<<std::endl;

	/*Ϊvector v��������������*/
	std::stack<int, std::vector<int>> s(v);

	/*
	 * ʹ��stack�ṩ�ķ�����������
	*/
	std::cout<<"�Զ��������ջ(stack����������)"<<std::endl;
	while(!s.empty())
	{
		std::cout<<s.top()<<" ";
		s.pop();
	}
	std::cout<<std::endl;
	std::cout<<"˵��"<<std::endl;
	std::cout<<"1. ����������ֻ������һ������������������������"<<std::endl;
	std::cout<<"2. �����������ĺ���ʵ����ʵҲ�ǻ�������������ĺ������������Լ����¶���ġ�"<<std::endl;
	std::cout<<std::endl;
}


template<class T,size_t MAX_SIZE=10>
class __SeqList
{
public:
	__SeqList();
private :
	T _array [MAX_SIZE];
	int _size ;
};

template <class T, size_t MAX_SIZE>
__SeqList<T, MAX_SIZE>::__SeqList()
	:_size(0)
{}

void test7(void)
{
	__SeqList<int> s1;
	__SeqList<int , 20> s2;
}


template <class T, int value>
T Add(const T& x)
{
	return x+value;
}

void test8(void)
{
	std::cout<<Add<int,10>(10)<<std::endl;
}