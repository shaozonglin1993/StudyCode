#pragma once

#include <assert.h>

class String
{
public:
	String(const char* str = "")
	{
		int len = strlen(str);			//�ַ�������
		_capacity = len + 1;				//�ַ�������'\0'��1
		_size = len;						//�ַ�������
		_str = new char[_capacity];		//���ٿռ�
		strcpy(_str, str);				//��_str�����ݿ�����_str��
	}

	//��������
	void _Swap(String& s)			//���ô���
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	String(const String& s)
		:_str(new char[1]()) //new char[1](NULL)
	{
		String tmp = s._str;
		_Swap(tmp);
	}

	//��������
	~String()  
	{
		if (_str)
		{
			delete[]_str;
			_str = NULL;
		}
	}

	void Display()
	{
		cout << _str << endl;
	}

	/********************************************************/
	/***********************���ظ��������*******************/
	/********************************************************/
	
	String& operator=(String s)
	{
		String _Swap(s);
		return* this;
	}

	bool operator>(const String& s)
	{
		return strcmp(_str, s._str) > 0 ? true : false;
	}

	bool operator<(const String& s)
	{
		return strcmp(_str, s._str) > 0 ? false : true;
	}

	bool operator==(const String& s)
	{
		return strcmp(_str, s._str) == 0 ? true : false;
	}

	bool operator>=(const String& s)
	{
		return strcmp(_str, s._str) >= 0 ? true : false;
	}

	bool operator<=(const String& s)
	{
		return strcmp(_str, s._str) <= 0 ? true : false;
	}

	/************************************************************/
	/***********************ʵ��String��������*******************/
	/************************************************************/

	//β��
	void PushBack(char ch)
	{
		_CheckCapacity(_size + 2);

		_str[_size++] = ch;
		_str[_size] = '\0';
	}

	//posλ�ò����ַ�ch
	void Insert(size_t pos, char ch)
	{
		assert(pos <= _size);
		_CheckCapacity(_size + 2);
		int end = _size + 1;
		while (end >= pos)
		{
			_str[end] = _str[end - 1];
			--end;
		}
		_str[pos - 1] = ch;
		++_size;
	}

	/*
	int len = 1;
	_size += len;
	_str = _CheckCapacity();
	for (size_t i = _size; i >= pos; i++)
	{
		_str[i] = _str[i - 1];
	}
	_str[pos - 1] = ch;
	*/

	//posλ�ò���һ���ַ���* str
	void Insert(size_t pos, const char* str)
	{
		assert(pos <= _size);

		size_t strSize = strlen(str);
		_CheckCapacity(_size + 1 + strSize);

		int end = _size;
		while (end >= (int)pos)
		{
			_str[end + strSize] = _str[end];
			--end;
		}
		while (*str)
		{
			_str[pos++] = *str++;
		}
		_size += strSize;
	}

	char& operator[](size_t index)
	{
		return _str[index];
	}

	//Findһ���ַ�
	int Find(char ch)
	{
		for (size_t i = 0; i < _size; i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return -1;
	}

	//Findһ���ַ���
	int Find(const char* str)
	{
		const char* pscr = _str;
		const char* psub =  str;

		int scrlen = _size;
		int sublen = strlen(str);

		int scrIndex = 0;
		while (scrIndex <= scrlen - sublen)
		{
			int i = scrIndex;
			int j = 0;
			while (scrlen > i && j < sublen && pscr[i] == psub[j])
			{
				i++;
				j++;
			}
			if (j == sublen)
			{
				return scrIndex;
			}
			scrIndex++;
		}
		return -1;
	}

	//ɾ��posλ�ú��n���ַ�
	void Erase(size_t pos, size_t n)
	{
		assert(pos < _size);
		for (size_t i = pos; i < _size; i++)
		{
			_str[i] = _str[i + n];
		}
		_size -= n;
	}

	//ɾ��posλ�õ��ַ�
	void Erase(size_t pos)
	{
		assert(pos < _size);
		for (size_t i = pos; i < _size; i++)
		{
			_str[i] = _str[i + 1];
		}
		_size--;
	}


private:
	//���ָ��ָ��ռ�Ĵ�С����������
	void _CheckCapacity(size_t size)
	{
		if (size >= _capacity)
		{
			int newCapacity = size > 2 * _capacity ? size : 2 * _capacity;
			_str = (char*)realloc(_str, newCapacity);
			_capacity = newCapacity;
		}
	}

	char *_str;          //�ַ���ָ��
	size_t _size;		//�ַ�������
	size_t _capacity;		//�ַ����ռ��С
};


//����
void Test1()
{
	String s1("hello world");
	s1.Display();
	String s2(s1);
	s2.Display();
	String s3("change world");
	s1 = s3;
	s1.Display();
}

void Test2()
{
	String s1("ello world");
	s1.Insert(1, 'h');
	s1.Display();
}

void Test3()
{
	String s1("hello rld");
	char* str = "wo";
	s1.Insert(6, str);
	s1.Display();
}

void Test4()
{
	String s1("hello");
	cout << s1[0] << endl;
}
void Test5()
{
	String s1("hello world");
	cout << s1.Find("ll") << endl;
}

void Test6()
{
	String s1("hello world");
	s1.Erase(2, 3);
	s1.Display();
}