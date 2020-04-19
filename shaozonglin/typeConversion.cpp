/***************************************************************
**	Copyright(c) 2019 VisionMC
**	File Name: typeConversion.cpp
**	Auther: Zonglin Shao  Version: 1.0  Data: 2019-5-14
**	Description: 
**		 C++����ǿ������ת��
**		 static_cast/reinterpret_cast/const_cast/dynamic_cast
**        explicit�ؼ���
**	History:null
***************************************************************/
#include <iostream>
#include "typeConversion.h"


void staticCast()
{
	int liv_i = 10;
	double ldv_d = static_cast<double>(liv_i);
	printf("%s \n","static_cast���ڷǶ�̬���͵�ת������̬ת����,�κα�׼ת����������������������������������ص����ͽ���ת����");
	//std::cout<<liv_i<<", "<<ldv_d<<std::endl;
	printf("int liv_i = %d, double ldv_d = %2f\n",liv_i,ldv_d);
}

int DoSomething (int i)
{
	std::cout<<"_FUNC_: DoSomething"<<std::endl;
	return 0;
}

void reinterpretCast()
{
	//
	// reinterpret_cast�����ñ�������FUNC�Ķ��巽ʽȥ���� DoSomething����
	// ���Էǳ���BUG������ת������ָ��Ĵ����ǲ�����ֲ�ģ����Բ�����������
	// C++����֤���еĺ���ָ�붼��һ����ʹ�ã�������������ʱ�������ȷ���Ľ��
	//
	printf("%s \n","reinterpret_cast���������ڽ�һ������ת��Ϊ��һ�ֲ�ͬ�����͡�");
	FUNC f = reinterpret_cast< FUNC>(DoSomething );
	f();
}

void constCast()
{
	printf("%s\n","const_cast��õ���;����ɾ��������const���ԣ����㸳ֵ��");
	const int liv_a = 2;
	int* p = const_cast<int*>(&liv_a);
	*p = 3;//δ������Ϊ

	std::cout<<"&liv_a = "<<&liv_a<<std::endl<<"p = "<<p<<std::endl;
	std::cout<<"liv_a��ֵû�иı� "<<liv_a<<std::endl;
}

/*����һ�����*/
void InputInt(int *num)
{
	//
}
void constCastTest1(void)
{
	printf("�ں��������Ĵ�����const_cast�����ò����ֳ�����\n");
	const int liv_num = 10;
	//InputInt(&liv_num); /*���Ͳ�����*/
	 InputInt(const_cast<int*>(&liv_num)); /*OK*/
}

/*����һ�����*/
void constCastTest2(void)
{
	printf("����һ����const�ı�����ȴʹ��һ��ָ��constֵ��ָ����ָ�������ڳ����ĳ���ı����������ֵ��ʹ��const_cast��\n");
	std::cout<<"�����constCast()�е�δ������Ϊ"<<std::endl;
}


class Base
{
public:
	virtual void f()
	{}
};

class Device:public Base
{
};

void fun(Base *pb)
{
	// dynamic_cast���ȼ���Ƿ���ת���ɹ����ܳɹ���ת���������򷵻�
	Device* pd1 = static_cast<Device*>(pb);
	Device* pd2 = dynamic_cast<Device*>(pb);
	std::cout<<"pd1:" <<pd1<<std::endl;
	std::cout<<"pd2:" <<pd2<<std::endl;
}


void dynamicCast()
{
	printf("dynamic_cast���ڽ�һ����������ָ��ת��Ϊ��������ָ������ã���̬ת����\n\
	����ת�ͣ��������ָ��->����ָ��/���ã�����Ҫת����\n\
	����ת�ͣ��������ָ��->����ָ��/���ã���dynamic_castת���ǰ�ȫ�ģ�\n\
	1.  dynamic_castֻ�����ں����麯������\n\
	2.  dynamic_cast���ȼ���Ƿ���ת���ɹ����ܳɹ���ת���������򷵻�0\n");
	Base b;
	Device d;
	fun(&b);
	fun(&d);
}


/*
** ��ǿת�У����ڵ������Ĺ��캯����֧����ʽ���͵�ת�������Ե����ǲ�
**��Ҫ��ʽ���͵�ת����ʱ�����ǾͿ��Լ���explicit�ؼ�������ֹ����
**���캯����ʱ������ʽ���͵�ת����
*/
class A
{
public :
	/*���������๹�캯������ʽ����ת����*/
	//explicit A (int a)
	A(int a)
	{
		std::cout<<"A(int a)" <<std::endl;
	}
	A(const A& a)
	{
		std::cout<<"A(const A& a)" <<std::endl;
	}
private :
	int _a ;
};

/*���Ǽ��Ϲؼ��ֺ��� = ��������ʽ����ת�����Ǳ��벻��ͨ���ġ�*/
/*������ǲ��ӾͿ���ͨ��*/
void ExplicitTest(void)
{
	A a1(1);
	// ��ʽת��-> A tmp(1); A a2(tmp);
	A a2 = 1;
}