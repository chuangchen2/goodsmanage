#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "depend.h"


int goodsCmp(const Goods* a, const Goods* b) {//�ȽϺ�����������Ϊ����
	int r;
	r = strcmp(a->gdsNo, b->gdsNo);
	if (r >= 0) {
		return False;
	}
	else return True;
}

void sort(const Goods* begin, const Goods* end, int* res, int (*compar)(const Goods* a, const Goods* b)) {//��������constָֻ���������ı���������
	int i;
	int leng = end - begin;
	int temp;
	while (leng--) {//ð������
		for (i = 0; i < leng; i++) {
			if (!(*compar)(begin+res[i], (begin+res[i+1]))) {	//��ƽ������ĵ�i���͵�i+1���Ա�
				temp = res[i];
				res[i] = res[i + 1];
				res[i + 1] = temp;
			}
		}
	}

}

void goodsSort(const Goods* g, int (*cmp)(const Goods* a, const Goods* b),int  tag) {	//tag����Ϊ�ж�ʹ�����ַ�����ӡ
	system("cls");
	int res[100];
	int i;
	for (i = 0; i < getGdsLength(g); i++) {
		res[i] = i;
	}
	sort(g, g+getGdsLength(gds)-1, res, cmp);
	if (tag) {	//��Ϊ1���ӡ����1
		printf("��Ʒ���\t��Ʒ�������\t��Ʒ����\t�������\t����\t�ܽ��\n");
		for (i = 0; i < getGdsLength(g)-1-1; i++) {
			printf("%s\t%-16s%s\t\t%d\t\t%.2f\t%.2f\n", g[res[i]].gdsNo, g[res[i]].catName, g[res[i]].gdsName, gds[res[i]].stock, g[res[i]].price, (float)g[res[i]].sales * g[res[i]].price);
		}
	}		
	else {		//��Ϊ0���ӡ����6
		printf("��Ʒ���\t��Ʒ����\t�������\t��������\t����\n");
		for (i = 0; i < getGdsLength(g) - 1; i++)
		{
			printf("%5s\t%5s\t\t%5d\t\t%5d\t\t%.2f\n", g[res[i]].gdsNo, g[res[i]].gdsName,
				g[res[i]].stock, g[res[i]].sales, g[res[i]].price);
		}
	}
	system("pause");
}