#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "depend.h"

void displayGoods(int* para, int n);

void disGoodsIofo()
{
	int i = 0;
	int para[50];
	while (strcmp(gds[i].gdsNo, "0") != 0)
	{
		para[i] = i;
		i++;
	}
	para[i] = i;
	displayGoods(para, i - 1);
	return;
}
void displayGoods(int* para, int n)
{
	system("cls");
	int i;
	int k;
	char temp[20];
	char temp1[20];
	for (i = 0; strcmp(gds[para[i]].gdsNo, "0") != 0; i++)
	{
		printf("%s\t%s\n", gds[para[i]].gdsNo, gds[para[i]].gdsName);
	}
	printf("����Ʒ��Ų�ѯ���밴1\n����Ʒ���Ʋ�ѯ�밴2\n");
	printf("����������1��2ȷ����ѯ��ʽ��");
	scanf("%d", &k);
	printf("\n");
	switch (k)
	{
	case 1: {
		printf("��������Ҫ��ѯ����Ʒ��ţ�");
		scanf("%s", &temp);
		for (i = 0; i < n; i++)
		{
			if (strcmp(temp, gds[i].gdsNo) == 0)
			{
				printf("\n");
				printf("��Ʒ���\t��Ʒ����\t�������\t��������\t����\n");
				printf("%5s\t%5s\t\t%5d\t\t%5d\t\t%.2f", gds[para[i]].gdsNo, gds[para[i]].gdsName,
					gds[para[i]].stock, gds[para[i]].sales, gds[para[i]].price);
			}
		}
		break;
	}
	case 2: {
		printf("��������Ҫ��ѯ����Ʒ���ƣ�");
		scanf("%s", &temp1);
		for (i = 0; i < n; i++)
		{
			if (strcmp(temp1, gds[i].gdsName) == 0)
			{
				printf("\n");
				printf("��Ʒ���\t��Ʒ����\t�������\t��������\t����\n");
				printf("%5s\t%5s\t\t%5d\t\t%5d\t\t%.2f", gds[para[i]].gdsNo, gds[para[i]].gdsName,
					gds[para[i]].stock, gds[para[i]].sales, gds[para[i]].price);
			}
		}
		break;
	}
	}
	printf("\n");
	system("pause");
	//printf("press any key to the meun:");
	return;
}

