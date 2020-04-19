#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

/*ordinary function*/
bool IsEqual(int left, int right);
bool IsEqual(const std::string& left, const std::string& right);
void test1(void);

/*template function*/
template<typename T>
bool _IsEqual(const T& left, const T& right);
void test2(void);
void test3(void);

/*overload template function*/
template<class T1, class T2>
bool _IsEqual(const T1& left, const T2& right);

/*ordinary class*/
typedef int DataType;
class SeqList;

/*template class*/
template<typename T>
class _SeqList;
/*��̬˳���*/
void test4(void);

/*Container adapter*/
/*ģ�����*/
template<class T,class Container>
	class Stack;
void test5(void);

/*ģ���ģ�����*/
template<class T,template<class> class container>
class _Stack;
void test6(void);

/*��׼����������ʹ��*/
void test9(void);

/*�����͵���ģ�����*/
template<class T,size_t MAX_SIZE>
class __SeqList;
void test7(void);

/*�����͵�ģ�庯������*/
template <class T, int value>
T Add(const T& x );
void test8(void);

/*��������������ǲ�������Ϊ������ģ�������*/



#endif	/*end of file*/