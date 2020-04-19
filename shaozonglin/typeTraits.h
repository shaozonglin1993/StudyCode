#ifndef _TYPE_TRAITS_H_
#define _TYPE_TRAITS_H_


struct __TrueType
{
	bool Get()
	{
		return true ;
	}
};

struct __FalseType
{
	bool Get()
	{
		return false ;
	}
};
//
// ʹ�ò����Ƶ�����ȡ����
//
template<class T>
void Copy(const T* src, T* dst, size_t size, __FalseType);

template<class T>
void _Copy(const T* src, T* dst, size_t size, __TrueType);

//
// ʹ����ȡ�ж����͵�Get�����ж��Ƿ���POD����������
//
template<class T>
void __Copy(const T* src, T* dst, size_t size);

/*Test Case*/
void typeTraits_test1(void);



#endif	/*end of file*/