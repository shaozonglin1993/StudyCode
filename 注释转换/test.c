#include "notes.h"

int main()
{
	FILE *fin, *fout;
	char p[100];

	printf("������Ҫת�����ļ�·����\n");
	scanf("%s", &p);
	
	if ((fin = fopen(p, "r")) == NULL)
	{
		printf("�޷���ԭ�ļ���\n");
		exit(0);
	}

	if ((fout = fopen("C:\\Users\\john\\Desktop\\output.txt", "w")) == NULL)
	{
		printf("�޷��������ļ���\n");
		exit(0);
	}

	covert(fin, fout);

	fclose(fin);
	fclose(fout);

	system("pause");
	return(0);
}