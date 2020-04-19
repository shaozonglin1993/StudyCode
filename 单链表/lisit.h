#pragma once

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef int DataType;			//��������������

typedef struct _node			//����ڵ�ṹ��
{
	DataType data;			//����
	struct _node* next;		//ָ����һ���ڵ��ָ��
}ListNode;

void InitList(ListNode** head)			//��ʼ��head
{
	*head = NULL;
}

ListNode* CreatNode(DataType val)
{
	ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
	assert(tmp);
	tmp->data = val;
	tmp->next = NULL;
	return tmp;
}

void PushBack(ListNode** head, DataType x)
{
	assert(head);
	if (*head == NULL)			//������
	{
		*head = CreatNode(x);
	}
	else							//�ǿ�����
	{
		ListNode* tail = *head;
		while (tail->next)
		{
			tail = tail->next;
		}
		tail->next = CreatNode(x);
	}
}


void ShowList(ListNode* head)
{
	assert(head);
	ListNode* cur = head;
	while (cur)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

void PushHead(ListNode** head, DataType x)
{
	//if (NULL == *head)				//������
	//{
	//	*head = CreatNode(x);
	//}
	//else							//�ǿ�����
	//{
	//	ListNode* tmp = CreatNode(x);
	//	tmp->next = *head;
	//	*head = tmp;
	//}

	ListNode* tmp = CreatNode(x);			//û�з�������ƺ�û��ʲô����
	tmp->next = *head;
	*head = tmp;
}


void PopBack(ListNode** head)
{
	if (NULL == *head)				//������
	{
		printf("list is empty!");
		return;
	}
	else if (NULL == (*head)->next)			//ֻ��һ���ڵ�
	{
		free(*head);
		*head = NULL;
	}
	else										//����ڵ�
	{
		ListNode* tail = *head;
		ListNode* pre = *head;
		while (tail->next)
		{
			pre = tail;
			tail = tail->next;
		}
		pre->next = NULL;
		free(tail);
	}
}

void PopFront(ListNode** head)
{
	if (NULL == *head)		//������
	{
		printf("list is empty!");
		return;
	}
	else                     //�ǿ�����
	{
		ListNode* tag = *head;
		*head = (*head)->next;
		free(tag);
	}
}

ListNode* Find(ListNode** head, DataType x)
{
	ListNode* cur = *head;
	while (cur)
	{
		if (cur->data == x)
		{
			return cur;
		}
		
		cur = cur->next;
	}
	return NULL;
}

void Insert(ListNode* pos, DataType x)			//��posλ�ý��в���
{
	assert(pos);
	ListNode* new_node = CreatNode(x);
	ListNode* tmp = pos->next;
	new_node->data = pos->data;			//��x��ֵ��pos->data,��pos->data��ֵ��pos->data;����˳��
	pos->data = x;
	pos->next = new_node;
	new_node->next = tmp;
}

void InsertFrontNode(ListNode* pos, DataType x)			//��posλ�õ�ǰ����в���
{
	assert(pos);
	ListNode* tmp = CreatNode(x);
	tmp->next = pos->next;
	pos->next = tmp;
	tmp->data = pos->data;

	pos->data = x;
	
}


void Erase(ListNode** head, ListNode* pos)
{
	assert(pos);
	if (pos == *head)			//��һ���ڵ�
	{
		*head = (*head)->next;
		free(pos);
	}
	else
	{
		ListNode* cur = *head;
		while (cur)
		{
			if (cur->next == pos)
			{
				cur->next = pos->next;
				free(pos);
				break;
			}
			cur = cur->next;
		}
	}
}

void DelNonTailNode(ListNode* pos)					//ɾ����β�ڵ�
{
	assert(pos && pos->next);
	
	ListNode* del = pos->next;			//��pos->next->data��ֵ��pos->data����pos->next  free,�ڴ�����
	ListNode* tmp = pos->next->next;
	pos->data = pos->next->data;
	pos->next = tmp;
	free(del);
}

void Remove(ListNode** head, DataType x)
{
	ListNode* remv = Find(head, x);
	if (remv)
	{
		Erase(head, remv);
	}
}

ListNode* Reverse(ListNode* head)
{
	ListNode* newHead = NULL;
	ListNode* cur = head;
	while (cur)
	{
		ListNode* tmp = cur;
		cur = cur->next;

		tmp->next = newHead;
		newHead = tmp;
	}
	return newHead;
}

void PrintTailtoHead(ListNode* head)		//�ݹ�ʵ�ִ�β��ͷ��ӡ
{
	if (head)
	{
		PrintTailtoHead(head->next);
		printf("%d ", head->data);
	}
}

ListNode* FindMid(ListNode* head)			//�������м����ݵ�λ�ò�����
{
	ListNode* slow = head;
	ListNode* fast = head;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}


DataType Find_TheLast_Knode(ListNode* head, int k)							//���ҵ�����K���ڵ㣬����һ��
{
	assert(head);
	ListNode* pre = head;						//��������ָ�룬�ֱ�ָ��ǰ��ͺ���
	ListNode* aft = head;
	int i = 1;
	while (aft)
	{
		if (i <= k)
		{
			aft = aft->next;
			i++;
		}
		else
		{
			aft = aft->next;
			pre = pre->next;
		}
	}									//ָ��aft��pre���־���Ϊ(k-1)����������֮��pre��Ϊ������K���ڵ�
	if ( i > k && k != 0)				//�����ڵ�����0���ڵ�
	{
		return pre->data;
	}
	else
		return -1;
}

void swap(DataType* n, DataType* m)		//����������
{
	DataType tmp = *n;
	*n = *m;
	*m = tmp;

}

void BubbleSort(ListNode** head)				//�����ð������
{
	assert(head);
	//һ���ڵ�
	if (NULL == (*head)->next)
	{
		return;
	}
	else
	{
		while (1)
		{
			ListNode* cur = (*head)->next;
			ListNode* p = *head;
			int exchange = 0;	//�����ж��Ƿ�������
			while (cur)
			{
				if (p->data > cur->data)
				{
					swap(&(p->data), &(cur->data));
					exchange = 1;
				}
				cur = cur->next;
				p   = p->next;
			}
			if (exchange == 0)  //һ��ѭ������δ����������return��������ѭ��						
			{
				return;
			}
		}
	}
}

ListNode* Merge_List(ListNode* l1, ListNode* l2)
{
	if (NULL == l1 || NULL == l2)
	{
		return l1 == NULL ? l2 : l1;
	}
	ListNode* newhead = CreatNode(0);
	ListNode* l = newhead;
	ListNode* cur1 = l1;
	ListNode* cur2 = l2;
	while (cur1 && cur2)
	{
		if (cur1->data > cur2->data)
		{
			l->next = cur2;
			l = l->next;
			cur2 = cur2->next;
		}
		else
		{
			l->next = cur1;
			l = l->next;
			cur1 = cur1->next;
		}
	}
	l->next= (cur1 == NULL ? cur2 : cur1);
	ListNode* tmp = newhead;
	newhead = newhead->next;
	free(tmp);
	tmp = NULL;
	return newhead;

}

ListNode* Joseph_Cycle(ListNode* head,int k)
{
	if (NULL == head)
	{
		printf("list is empty!\n");
		return NULL;
	}
	
	ListNode* cur = head;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	ListNode* tmp = NULL;
	cur->next = head;
	cur = head;
	int count = k;
	while (1)
	{
		count = k;
		if (cur->next != cur)
		{
			while (--count)
			{
				cur = cur->next;
			}
			tmp = cur->next;
			cur->data = cur->next->data;
			cur->next = cur->next->next;
			free(tmp);
		}
		else
		{
			cur->next = NULL;
			return cur;
		}
	}
}

ListNode* CreatCycle(ListNode* phead,int k)		//Ϊ��������һ����
{
	if (NULL == phead)			//pheadΪ��
	{
		printf("list is empty!\n");
		return NULL;
	}
	ListNode* pos = Find(&phead, k);
	if (pos == NULL)
	{
		printf("k is error!\n");
	}

	ListNode* pos1 = pos;
	ListNode* tail = phead;
	while (tail->next)			//�ҵ�list��β�ڵ�
	{
		tail = tail->next;
	}
	tail->next = pos1;			//list��β�ڵ�*nextָ��pos 
	tail = phead;				//cur ָ��ͷ���
	return tail;
}

int IsLoop(ListNode* phead)			//�ж������Ƿ��л����л�����1�����򷵻�-1��
{
	if (NULL == phead)
	{
		printf("list is empty!\n");
		return -1;
	}
	ListNode* slow = phead;	//��ָ�� 
	ListNode* fast = phead;	//��ָ��
	while (fast && fast->next)	
	{
		fast = fast->next->next;	//fast = 2*slow
		slow = slow->next;
		if (&slow->data == &fast->data)
		{
			return 1;
		}
	}
	return -1;
}

ListNode* MeetNode(ListNode* phead)		//���ؿ���ָ���ڻ��������Ľڵ�,ͬʱҲ�����ж��Ƿ���ڻ�
{
	if (NULL == phead)
	{
		printf("list is empty!\n");
		return -1;
	}
	ListNode* slow = phead;	//��ָ�� 
	ListNode* fast = phead;	//��ָ��
	while (fast && fast->next)
	{
		fast = fast->next->next;	//fast = 2*slow
		slow = slow->next;
		if (&slow->data == &fast->data)			//if(slow == fast);
		{
			return slow;
		}
	}
	return NULL;
}

int GetLength(ListNode* phead)		//������Ľڵ����
{
	int count = 0;
	ListNode* cur = phead;
	if (NULL == phead)		//�ձ�
	{
		return count;
	}
	else				//�ǿձ�	
	{
		while (cur)
		{
			cur = cur->next;
			count++;
		}
		return count;
	}
}

ListNode* GetEnterNode(ListNode* phead)		//���л�������Ļ�����ڽڵ�
{
	ListNode* meet = MeetNode(phead);	//�ж�list�Ƿ���ڻ�

	if (NULL == meet)				    //û�л������
	{
		printf("there is no cycle in the list!\n");	
		return NULL;
	}
	else								//�л������
	{
		ListNode* tar = meet;
		ListNode* cur = phead;
		while (tar != cur)			//2*��L + X��=L + X + nC   L = nC - X
		{
			cur = cur->next;
			tar = tar->next;
		}
		return cur;			//���ػ���ڽڵ�
	}
}










