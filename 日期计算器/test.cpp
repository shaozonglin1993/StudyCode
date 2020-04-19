#include <iostream>
#include <assert.h>
using namespace std;

//int Month1[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//int Month2[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

////�����жϺ���
//	int Data::Leep_year(int year)
//	{
//		if ((year % 400) || ((year % 4) && !(year % 100)))
//		{
//			return 1;
//		}
//		else
//		{
//			return -1;
//		}
//	}



class Date
{
public:
//����display����
	void display();

//Data ���캯��
	Date(int year = 1900, int month = 1, int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{}


//���� - �����
Date operator-(int n)
{
	Date tmp(*this);
	tmp._day = tmp._day - n;
	if (n < 0)
	{
		return *this + (-n);
	}
	while (tmp._day <= 0)
	{
		if (tmp._month == 1)
		{
			tmp._month = 12;
			tmp._year = tmp._year - 1;
		}
		else
		{
			tmp._month = tmp._month - 1;
		}
		tmp._day = tmp._day + GetMonthDay(tmp._year, tmp._month);
	}
	return tmp;
}
//����+�����
Date operator+(int n)
{
	Date tmp(*this);
	if (n >= 0)					//n>=0�����
	{
		tmp._day = tmp._day + n;

		while (tmp._day > GetMonthDay(tmp._year,tmp._month))
		{
			tmp._day = tmp._day - GetMonthDay(tmp._year, tmp._month);
			if (tmp._month == 12)			//tmp.month=12����tmp.month+1Ϊ1
			{
				tmp._month = 1;
				tmp._year = tmp._year + 1;
			}
			else
			{
				tmp._month = tmp._month + 1;
			}
		}
	}
	else					//n<0�����
	{
		return (*this - (-n));
	}
	return tmp;
}

//����+=�����
Date& operator+=(int n)
{
	*this = *this + n;
	return *this;
}

//����-=�����
Date& operator-=(int day)
{
	*this = *this - day;
	return *this;
}

//����ǰ��++�����
Date& operator++()
{
	*this = *this + 1;
	return *this;
}

//���غ���++�����
Date operator++(int)
{
	Date tmp(*this);
	*this = *this + 1;
	return tmp;
}

//Date operator++(int)
//{
//	Date tmp(*this);
//	++(*this);
//	return tmp;
//}

//����ǰ��--�����
Date& operator--()
{
	*this = *this - 1;
	return *this;
}

//���غ���--�����
Date operator--(int)
{
	Date tmp(*this);
	*this = *this - 1;
	return tmp;
}

//Date operator--(int)
//{
//	Date tmp(*this);
//	--(*this);
//	return tmp;
//}

//����>�����
bool operator>(const Date& d)
{
	return (_year > d._year
		|| (_year == d._year&&_month > d._month)
		|| _year == d._year&&_month == d._month&&_day > d._day);
}

//bool operator>(const Date& d)
//{
//	if (_year > d._year)
//	{
//		return true;
//	}
//	else if (_year == d._year)
//	{
//		if (_month > d._month)
//		{
//			return true;
//		}
//		else if(_month == d._month)
//		{
//			if (_day > d._day)
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}

//����==�����
bool operator==(const Date& d)
{
	return _year==d._year
	&&_month==d._month
	&&_day==d._day;
}

//����<�����
bool operator<(const Date& d)
{
	return !(*this>d || *this == d);
}

//���أ�=�����
bool operator!=(Date& d)
{
	return !(*this == d);
}

//����<=�����
bool operator<=(const Date& d)
{
	return *this<d || *this==d;
}

//�������ڽ��������ֵ
int operator-(const Date& d)
{
	int flag = 1;
	Date max = *this;
	Date min = d;
	if (*this < d)
	{
		min = *this;
		max = d;
		flag = -1;
	}

	int days = 0;

	while (min != max)
	{
		++min;
		days++;		//�ۼӷ�
	}

	return flag*days;
}

friend istream& operator>>(istream& is, Date& d); //������Ԫ����
friend ostream& operator<<(ostream& os, const Date& d); //������Ԫ����

private:
	//����x�·ݵ�����
	int GetMonthDay(int year, int month)
	{
		assert(month > 0 && month < 13);
		static int monthArray[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = monthArray[month];
		if ((month == 2) && (year % 400) || (year % 4 && year % 100))
		{
			day += 1;
		}
		return day;
	}

	int _year;
	int _month;
	int _day;
};

//����display����
void Date::display()
{
	cout << _year << "-" << _month << "-" << _day << endl;
}

//����>>�����
istream& operator>>(istream& is, Date& d)
{
	cout<<"������һ�����ڵ�������:";
	is>>d._year>>d._month>>d._day;

	return is;
}

//����<<�����
ostream& operator<<(ostream& os, const Date& d)
{
	cout<<d._year<<"-"<<d._month<<"-"<<d._day<<endl;
	return os;
}


int main()
{
	int year = 1900, month = 1, day = 1;
	while (1)
	{
		cout << "������������ڣ� " << endl;
		cin >> year >> month >> day;
		Date d1(year, month, day);
		cout << "������������";
		cin >> day;
		cout << "����"<<day<<"��������ǣ�" << endl;
		d1 = d1 + day;
		d1.display();
	}
	system("pause");
	return 0;
}


//#include <iostream>
//#include <assert.h>
//using namespace std;
//
//class Date
//{
//public :
//	/*Date (int year = 1900, int month = 1, int day = 1)
//		:_year(year)
//		,_month(month)
//		,_day(day)
//	{}*/
//
//	Date (int year = 1900, int month = 1, int day = 1)
//		:_year(year)
//		,_month(month)
//		,_day(day)
//	{}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//class Test1
//{
//public:
//	Test1(int t = 0)
//	{
//		cout<<"Test1(int t = 0)"<<endl;
//		_t1 = t;
//	}
//
//	~Test1()
//	{
//		cout<<"~Test1()"<<endl;
//	}
//
//private:
//	int _t1;
//};
//
//int main()
//{
//	//Test1* p1 = (Test1*)malloc(sizeof(Test1));
//	//new(p1) Test1(10);
//
//	// new -> ����+���ù��캯����ʼ��
//
//	// malloc/operator new -> �����ڴ�
//	// new ��λ���ʽ ->��ʾ���ù��캯����ʼ��
//
//	//Test1* array1 = new Test1[10];
//
//	//delete[] array1;
//
//	// ģ��new[]
//	Test1* array2 = (Test1*)operator new(sizeof(Test1)*10 + 4);
//	*((int*)array2) = 10;
//	array2 = (Test1*)((int)array2 + 4);
//	for (int i = 0; i < 10; ++i)
//	{
//		new(array2 + i) Test1(20);
//	}
//
//	// ģ��delete[]
//	// �ȵ��������������ͷſռ�
//	int count = *((int*)array2 - 1);
//	for (int i = 0; i < count; ++i)
//	{
//		array2[i].~Test1();
//	}
//	array2 = (Test1*)((int)array2 - 4);
//	operator delete(array2);
//
//	return 0;
//}