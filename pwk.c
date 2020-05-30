#include <stdio.h>
#include "depend.h"
#include <Windows.h>

void printGoodsSalesInfo(const Goods* g) {
	system("cls");
	int i;
	printf("商品编号\t商品名称\t库存数量\t销售数量\t单价\n");
	for (i = 0; i < getGdsLength(g)-1; i++)
	{
			printf("%5s\t%5s\t\t%5d\t\t%5d\t\t%.2f\n", gds[i].gdsNo, gds[i].gdsName,
				gds[i].stock, gds[i].sales, gds[i].price);
	}
	system("pause");
}


int goodsSalesCmp(const Goods* a, const Goods* b) {
	if (a->sales > b->sales) return 1;
	else return 0;
}

