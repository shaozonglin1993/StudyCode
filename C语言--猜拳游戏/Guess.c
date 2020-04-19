#define _CRT_SECURE_NO_WARNINGS 1

 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NAME_SIZE 50
#define PASSWORD_SIZE 20
#define NAME      "zhangsan"
#define PASSWORD  "123456"
//#define CONTINUE(X) {printf("&s",X);getchar();}

//player �ṹ��
typedef struct player{
	char name[NAME_SIZE];
	char password[PASSWORD_SIZE];
	int total_num;
	int victory;
}player_t;

player_t *player;

player_t * creat_player(void)
{
	player = (player_t *)malloc(sizeof(player_t)* 1);
	if (NULL == player)
	{
		return NULL;
	}
	memset(player, 0, sizeof(player_t));
	strcpy(player->name, NAME);
	strcpy(player->password, PASSWORD);
	player->total_num = 0;
	player->victory = 0;
	return player;
}

int my_rand()
{
	int computer_choice = 0;
	srand(time(NULL));
	computer_choice = (rand() % 3 + 1);
	return computer_choice;
}
destroy_player()
{
	if (NULL != player)
	{
		free(player);
	}
	player = NULL;
}
void load()
{
	int i = 0;
	for (i = 2; i > 0; i--)
	{
		system("cls");
		printf("���Գ�ȭ�У�%d\n", i);
		fflush(stdout);
		Sleep(1000);
	}
	printf("\n");
}

void menue()
{
	//	system("cls");
	printf("\n\n************��ȭ��Ϸ*************\n");
	printf("1:ʯͷ   2������   3����   0:�˳�\n");
	printf("������ȭ�� ");
}

void out_print(int player_choice, int computer_choice)
{
	if (player_choice == 1 && computer_choice == 1)
		printf("��ѡ��ʯͷ\n����Ҳѡ��ʯͷ\n");
	else if (player_choice == 1 && computer_choice == 2)
		printf("��ѡ��ʯͷ\n����ѡ�����\n");
	else if (player_choice == 1 && computer_choice == 3)
		printf("��ѡ��ʯͷ\n����ѡ��\n");
	else if (player_choice == 2 && computer_choice == 1)
		printf("��ѡ�����\n����ѡ��ʯͷ\n");
	else if (player_choice == 2 && computer_choice == 2)
		printf("��ѡ�����\n����Ҳѡ�����\n");
	else if (player_choice == 2 && computer_choice == 3)
		printf("��ѡ�����\n����ѡ��\n");
	else if (player_choice == 3 && computer_choice == 1)
		printf("��ѡ��\n����ѡ��ʯͷ\n");
	else if (player_choice == 3 && computer_choice == 2)
		printf("��ѡ��ʯͷ\n����ѡ�����\n");
	else if (player_choice == 3 && computer_choice == 3)
		printf("��ѡ��ʯͷ\n����Ҳѡ��\n");
}
void menue_ctr()
{
	int win = 0;
	int computer_choice = 0;
	int player_choice = 0;
	while (1)
	{
		menue();
		do
		{
			//	menue();
			scanf("%d", &player_choice);
		} while (player_choice > 3 || player_choice < 0);
		if (player_choice == 0)
		{
			return;
		}
		load();
		computer_choice = my_rand();
		win = player_choice - computer_choice;
		(player->total_num)++;
		//load();
		out_print(player_choice, computer_choice);
		switch (win)
		{
		case -1:
		case 2:
		{
				  printf("��ϲ��ʤ����\n");
				  (player->victory)++;
				  break;
		}
		case 0:
		{
				  printf("�;�\n");
				  break;
		}
		default:
		{
				   printf("�ٽ������������ˣ�");
		}
		}
	}
}


void victory_display(int total, int victory)
{

	double win = 0.0;
	win = (double)victory / (double)total;
	printf("\n\n\t\t   ���а�\n");
	printf("\t\t****************\n\n");
	printf("%10s %10s %10s %10s\n", "����", "�ܾ���", "ʤ��", "ʤ��");
	printf("%10s %10d %10d %10f\n", player->name, player->total_num, player->victory, win);
}

int main()
{
	player = creat_player();
	if (NULL == player)
	{
		return 1;
	}
	menue_ctr();
	victory_display(player->total_num, player->victory);
	system("pause");
	return 0;
}