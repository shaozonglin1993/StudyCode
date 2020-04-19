#define MAX_R 20		//�궨���ͼ������
#define MAX_C 10		//�궨���ͼ������

//����ṹ��,�ڵ�
typedef struct ListNode
{
	char ch;
	struct ListNode* next;
}ListNode;

ListNode* head = NULL;

//��ʼ��һ������
void Init(ListNode arr[][MAX_R])
{
	int i = 0, j = 0;
	for (i = 0; i < MAX_C; i++)
	{
		for (j = 0; j < MAX_C; j++)
		{
			arr[i][j].ch = ".";
		}
	}
}


//��ӡ̰���ߵ�ͼ
void PrintMap(ListNode arr[][MAX_R])
{
	printf("map\n");
	int i = 0, j = 0;
	for (i = 0; i < MAX_C; i++)
	{
		for (j = 0; j < MAX_R; j++)
		{
			if (arr[i][j].ch == '1')			//1  ��ͷ
			{
				arr[i][j].ch = '@';
				printf("%c", arr[i][j].ch);
			}
			else if (arr[i][j].ch == '2')		//2  ʳ��
			{
				arr[i][j].ch = '*';
				printf("%c", arr[i][j].ch);
			}
			else if (arr[i][j].ch == '3')		//3  ����
			{
				arr[i][j].ch = '*';
				printf("%c", arr[i][j].ch);
			}
			else
			{
				arr[i][j].ch = '.';
				printf("%c", arr[i][j].ch);
			}
		}
		printf("\n");
	}
	printf("\n");
}


//ʳ�������������
void Creat_Food(ListNode arr[][MAX_R])
{
	srand(time(0));
	int i = 0, j = 0;
	i = (rand() % MAX_C);
	j = (rand() % MAX_R);
	arr[i][j].ch = '2';

}

//���������ַ�����
void Button(ListNode arr[][MAX_R],size_t head,size_t tail)
{
	arr[head][tail].ch = '1';		//��ͷ��ʼ��λ��
	char key;
	if (_kbhit() != 0) //��鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0  
	{
		while (_kbhit() != 0)  //���ܴ��ڶ������,Ҫȫ��ȡ��,�����һ��Ϊ��  
		{
			key = getchar(); //�������ӿ���̨��ȡ�������浽key��  
		}
		switch (key)
		{
		case 56:
			head--;
			break;
			//8-��  
		case 50:
			head++;
			break;
			//2-��  
		case 52:
			
			break;
			//4-��  
		case 54:
			break;
			//6-��
		}
	}
}
//̰�����˶�����
//void SnakeMove(ListNode arr[][MAX_R])
//{
//	char ch;
//	int i = 5, j = 5;
//	//arr[i][j].ch = '1';		//��ͷ��ʼ��λ��
//	//arr[i][j].next = &arr[i + 1][j];
//	//arr[i + 1][j].ch = '3';
//	printf("�����룺");
//	scanf("%c", &ch);
//	switch (ch)
//	{
//	case'8':
//		if (arr[i - 1][j].ch == '2')
//		{
//			arr[i - 1][j].ch = '1';
//			arr[i - 1][j].next = &arr[i][j];
//			arr[i][j].ch = '3';
//		}
//		else
//		{
//			arr[i + 1][j].ch = '1';
//			arr[i + 1][j].next = &arr[i][j];
//			arr[i - 1][j].ch = '0';
//		}
//	}
//}

	//system("cls");	//ˢ��
	//Sleep(1000);

	//fflush(stdout);