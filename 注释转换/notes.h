/*********************��Ŀ��ע��ת��**2016-8-21***********************************
��Ŀ��飺��C++���ע��ת���ɴ�ͳC���ע�͵ĳ���//--> /*��
��    �ߣ�������
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*********************************************************************************
����ö�����ͣ�ע�����е�״̬������ȷ��ע��ת���ķ���
�ֱ������	nostate, cstate, cppstate, endstate
*********************************************************************************/
typedef enum
{
	nostate,
	cstate,
	cppstate,
	endstate
}STATEENUM;

/*********************************************************************************
����״̬���ṹ�� state_machine��ע��״̬�����ļ�ָ���״̬���ĵ�ǰ״̬
*********************************************************************************/
typedef struct state_machine
{
	FILE *inputfile;
	FILE *outputfile;
	STATEENUM state;
}STATE_MACHINE;

STATE_MACHINE go_state = { 0 };

/*********************************************************************************
ȫ�ֺ���ʡ��
void eventpro(char ch);
void eventproatno(char ch);
void eventproatc(char ch);
void eventproatcpp(char ch);
int	covert(FILE *fin, FILE *fout);
*********************************************************************************/
void eventpro(char ch);
void eventproatno(char ch);
void eventproatc(char ch);
void eventproatcpp(char ch);
void covert(FILE *fin, FILE *fout);

/*********************************************************************************
�������ƣ�covert
���������������ļ�ָ��
          FILE *fin  ��Ҫ�򿪵�Դ�ļ��ļ�ָ��
          FILE *fout �ض���Ŀ���ļ����ļ�ָ��
�������ܣ�״̬ת��
��������ֵ��void
*********************************************************************************/
void covert(FILE *fin, FILE *fout)
{
	if (fin == NULL || fout == NULL)
	{
		printf("Error: Argument Invalid!\n");
		return -1;
	}
	char ch;
	go_state.inputfile = fin;
	go_state.outputfile = fout;
	go_state.state = nostate;

	while (go_state.state != endstate)
	{
		ch = fgetc(go_state.inputfile);
		eventpro(ch);
	}
}
/*********************************************************************************
�������ƣ�eventro
����������char ch ��ԭ�ļ���ȡ�����ַ�
�������ܣ�״̬���������ж��ַ���ȷ����Ҫ���õ�״̬����
��������ֵ��void
*********************************************************************************/
void eventpro(char ch)
{
	switch (go_state.state)
	{
	case nostate:
		eventproatno(ch);
		break;
	case cstate:
		eventproatc(ch);
		break;
	case cppstate:
		eventproatcpp(ch);
		break;
	case endstate:
		printf("���н���\n");
		break;
	default:
		break;
	}
}

/*********************************************************************************
�������ƣ�eventproatno
����������char ch ��ԭ�ļ���ȡ�����ַ�
�������ܣ���״̬�������ж�ch����ȷ��״̬��״̬
��������ֵ��void
*********************************************************************************/
void eventproatno(char ch)
{
	char nextch;
	switch (ch)
	{
	case '/':
		nextch = fgetc(go_state.inputfile);
		if (nextch == '/')
		{
			fputc(ch, go_state.outputfile);
			fputc('*', go_state.outputfile);
			go_state.state = cppstate;
			break;
		}

		else if (nextch == '*')
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
			go_state.state = cstate;

		}
		else
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
		}
		break;
	case EOF:
		go_state.state = endstate;
		break;
	default:
		fputc(ch, go_state.outputfile);
		break;

	}
}

/*********************************************************************************
�������ƣ�eventproatcpp
����������char ch ��ԭ�ļ���ȡ�����ַ�
�������ܣ�cpp״̬������,��C++ע��ת����C����ע�ͣ���ȫC���Ե��Ұ벿��
��������ֵ��void
*********************************************************************************/
void eventproatcpp(char ch)
{
	char nextch;
	switch (ch)
	{
	case'*':
		nextch = fgetc(go_state.inputfile);
		if (nextch == '/')
		{
			fputc(' ', go_state.outputfile);
			fputc(' ', go_state.outputfile);
		}
		else
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
		}
		break;
	case'/':
		nextch = fgetc(go_state.inputfile);
		if (nextch == '/' || nextch == '*')
		{
			fputc(' ', go_state.outputfile);
			fputc(' ', go_state.outputfile);
		}
		else
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
		}
		break;
	case'\n':
	{
				fputc('*', go_state.outputfile);
				fputc('/', go_state.outputfile);
				fputc('\n', go_state.outputfile);
				go_state.state = nostate;
	}
		break;

	case EOF:
	{
				fputc('*', go_state.outputfile);
				fputc('/', go_state.outputfile);
				go_state.state = endstate;
	}
		break;
	default:
		fputc(ch, go_state.outputfile);
		break;
	}
}

/*********************************************************************************
�������ƣ�eventproatc
����������char ch ��ԭ�ļ���ȡ�����ַ�
�������ܣ�C״̬����������ȫC����ע��
��������ֵ��void
*********************************************************************************/
void eventproatc(char ch)
{
	char nextch;
	switch (ch)
	{
	case '*':
		nextch = fgetc(go_state.inputfile);
		if (nextch == '/')
		{
			fputc('*', go_state.outputfile);
			fputc('/', go_state.outputfile);
			go_state.state = nostate;
		}
		else
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
		}
		break;
	case EOF:
	{
				go_state.state = endstate;
	}
		break;
	case'/':
		nextch = fgetc(go_state.inputfile);
		if (nextch == '/')
		{
			fputc(' ', go_state.outputfile);
			fputc(' ', go_state.outputfile);
		}
		else if (nextch == '*')
		{
			fputc(' ', go_state.outputfile);
			fputc(' ', go_state.outputfile);
		}
		else
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
			//	/**XXXXX**/
			//	/*XXXXX*/
			//��һ�н���״̬û���ÿգ��ᵼ����һ�γ������⣻�ڶ��л��� �ո�ո�XXXXX*/
			go_state.state = nostate;  
		}
		break;
	default:
		fputc(ch, go_state.outputfile);
		break;
	}
}