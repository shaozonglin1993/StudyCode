#pragma once			//ֻ����һ��

#include <memory.h>
#include<assert.h>
#include <stdio.h>

#define  MAX_SIZE 100
typedef int DataType;			 //��������������
typedef struct SeqList		 //����ṹ������
{
	DataType array[MAX_SIZE];	 // ���ݶ�
	size_t size;				 // ���ݸ���
}SeqList;


//��ʼ���ṹ�����

void InitSeqList(SeqList* pSeq)
{
	memset(pSeq->array, 0, sizeof(DataType)*MAX_SIZE);
	pSeq->size = 0;
}


//��ӡ�ṹ�����

void PrintSeqList(SeqList* pSeq)			
{
	size_t i = 0;
	assert(pSeq);

	for (i = 0; i < pSeq->size; i++)
	{
		printf("%d ", pSeq->array[i]);
	}

	printf("\n");
}


//�ڽṹ�������������������x

void PushBack(SeqList* pSeq, DataType x)		
{
	assert(pSeq);
	if (pSeq->size >= MAX_SIZE)			//�ж�˳����Ƿ��Ѿ�����
	{
		printf("list is full��\n");
		return;
	}
	pSeq->array[pSeq->size++] = x;	
}


//ɾ�������һ����ЧԪ��

void PopBack(SeqList* pSeq)			
{
	assert(pSeq);		//ָ���п�
	if (pSeq->size == 0)	//˳����п�
	{
		printf("list is empty!\n");
		return;
	}
	//pSeq->size--;					//pSeq->size - 1;ֱ��size-1��ɾ��δ֪������Ϊ����
	pSeq->array[--pSeq->size] = 0;		//pSeq->size - 1 && pSeq->array[p->size-1]=0;��������
}


//��˳�����ǰ�����һ��x

void PushFront(SeqList* pSeq, DataType x)		
{
	assert(pSeq);
	int begin = pSeq->size - 1;		//�����±�Ϊ���ݸ�����1��
	if (pSeq->size >= MAX_SIZE)		//˳����ж��Ƿ��Ѿ�����
	{
		printf("list is full!\n");
		return;
	}
	for (; begin >= 0; begin--)
	{
		pSeq->array[begin + 1] = pSeq->array[begin];		//������������ƶ�һλ����ֵx��p->array[0];
	}
	pSeq->array[0] = x;
	pSeq->size++;			//size+1��

}


//ɾ��˳�������λԪ��

void PopFront(SeqList* pSeq)		
{
	assert(pSeq);		//ָ���п�
	int i = 1;
	if (pSeq->size <= 0)	//˳����п�
	{
		printf("list is empty!\n");
		return;
	}
	for (i = 1; i < pSeq->size; i++)
	{
		pSeq->array[i - 1] = pSeq->array[i];			//����Ԫ��ǰ��һλ
	}
	pSeq->size--;				//size-1
}


//��pos λ�� ����x

void Insert(SeqList* pSeq, size_t pos, DataType x)  
{
	assert(pSeq);	//ָ���п�
	size_t end = pSeq->size - 1;
	if (pSeq->size >= MAX_SIZE)		
	{
		printf("list is full!\n");		//˳�������
		return;
	}
	for (; end >= pos; end--)
	{
		pSeq->array[end + 1] = pSeq->array[end];		//posλ�ü��Ժ��Ԫ��ȫ������һλ��posλ����Ϊx
	}
	pSeq->array[pos] = x;		
	pSeq->size++;		//�������ݣ�size ��1
}


//Ѱ��x��λ��

int Find(SeqList* pSeq, DataType x)		
{
	assert(pSeq);		//ָ���п�
	if (pSeq->size <= 0)	//˳����п�
	{
		printf("list is empty!\n");
		return -1;
	}
	rsize_t i = 0;
	for (i = 0; i < pSeq->size; i++)
	{
		if (pSeq->array[i] == x)
		{
			return i;		//��������x ���±�ֵ
		}
	}
	return -1;		//δ�ҵ�x���� -1
}


// ɾ��posλ�õ�����

void Erase(SeqList* pSeq, size_t pos)		
{
	assert(pSeq);				//ָ���п�
	if (pos >= pSeq->size)		//posֵerror
	{
		printf("pos is error!\n");
		return;
	}
	rsize_t i = pos;				//posֵOK
	for (; i < pSeq->size-1; i++)
	{
		pSeq->array[i] = pSeq->array[i + 1];		//posλ��posλ���Ժ��ȫ������ǰ��һλ
	}
	pSeq->array[i + 1] = 0;		//���һλ����Ϊ0
	pSeq->size--;				//size-1
}


// ɾ���ҵ��ĵ�һ��x

void Remove(SeqList* pSeq, DataType x)		
{
	assert(pSeq);		//ָ���п�
	size_t i = 0;
	for (; i < pSeq->size; i++)
	{
		if (pSeq->array[i] == x)
		{
			size_t ret = Find(pSeq, x);		//����Find�����ҵ�X��λ��
			Erase(pSeq, ret);					//����Erase����ɾ��������Ԫ��
		}
	}									//pSeq->size���ü�1��Erase�Ѿ�������
}


//ɾ�����е�x
//˼·������������ֵͬ�±꣨preIndex��aftIndex�������ҵ�X��aftIndex��1 ��preIndex�����¼X��λ�ã���
//�±�aftIndexֵΪX����Ԫ�ظ�ֵ��preIndexλ��

void RemoveAll(SeqList* pSeq, DataType x)		
{
	assert(pSeq);		//ָ���п�
	int count = 0;
	int preIndex = 0;		
	int aftIndex = 0;
	while (preIndex < pSeq->size)
	{
		if (pSeq->array[aftIndex] != x)		//Ѱ��˳����е�X
		{
			pSeq->array[preIndex] = pSeq->array[aftIndex];	
			preIndex++;
		}
		else
		{
			count++;
		}
		aftIndex++;
	}
	pSeq->size -= count;			//size-ɾ����X�ĸ���
}


//ð���������ظ����߷ù�Ҫ��������У�һ�αȽ�����Ԫ�أ�������ǵ�˳�����Ͱ����ǽ�
//���������߷����еĹ������ظ��ؽ���ֱ��û������Ҫ������Ҳ����˵�������Ѿ��������

void BubbleSort(SeqList* pSeq)			
{
	int begin = 1;
	int end = pSeq->size;
	assert(pSeq);

	for (; end > 0; --end)
	{
		int exchange = 0;
		for (begin = 1; begin < end; begin++)				//��forѭ����һ������������д
		{
			if (pSeq->array[begin - 1] > pSeq->array[begin])
			{
				DataType tmp = pSeq->array[begin - 1];
				pSeq->array[begin - 1] = pSeq->array[begin];
				pSeq->array[begin] = tmp;
				exchange = 1;
			}
		}

		if (exchange == 0)
		{
			return;
		}
	}
}


//ѡ������
//ѡ������Selection sort����һ�ּ�ֱ�۵������㷨�����Ĺ���ԭ����ÿһ�δӴ����������Ԫ����ѡ����С������󣩵�һ��Ԫ�أ������
//���е���ʼλ�ã�ֱ��ȫ�������������Ԫ�����ꡣ ѡ�������ǲ��ȶ������򷽷�����������[5�� 5�� 3]��һ�ξͽ���һ��[5]��[3]����������
//��һ��5Ų�����ڶ���5���棩��

void SeclectSort(SeqList* pSeq)			
{

}


//�ǵݹ�ʵ�ֶ��ַ�����

int BinarySearch(SeqList* pSeq, DataType x)			
{
	int left = 0;
	int right = pSeq->size;						//pSeq->array[pSeq->size] ���������Ԫ�أ�����������Ԫ��
	assert(pSeq);

	while (left < right)
	{
		int mid = left + (right - left) / 2;
		if (pSeq->array[mid] < x)
		{
			left = mid + 1;
		}
		else if (pSeq->array[mid] > x)
		{
			right = mid;
		}
		else
		{
			return mid;
		}
	}

	return -1;
}


//�ݹ�ʵ�ֶ��ַ�����

int _BinarySearch_R(SeqList* pSeq, int left, int right, DataType x)  
{
	assert(pSeq);
	int mid = 0;
	if (left < right)
	{
		mid = left + (right - left) / 2;

		if (pSeq->array[mid] < x)
		{
			return _BinarySearch_R(pSeq, mid + 1 , right, x);			
		}
		else if (pSeq->array[mid] > x)
		{
			return _BinarySearch_R(pSeq, left, mid, x);
		}
		else
		{
			return mid;
		}
	}
	return -1;
}


