#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "depend.h"


int goodsCmp(const Goods* a, const Goods* b) {//比较函数，以升序为规则
	int r;
	r = strcmp(a->gdsNo, b->gdsNo);
	if (r >= 0) {
		return False;
	}
	else return True;
}

void sort(const Goods* begin, const Goods* end, int* res, int (*compar)(const Goods* a, const Goods* b)) {//排序函数，const指只读变量不改变数组数据
	int i;
	int leng = end - begin;
	int temp;
	while (leng--) {//冒泡排序
		for (i = 0; i < leng; i++) {
			if (!(*compar)(begin+res[i], (begin+res[i+1]))) {	//将平行数组的第i个和第i+1个对比
				temp = res[i];
				res[i] = res[i + 1];
				res[i + 1] = temp;
			}
		}
	}

}

void goodsSort(const Goods* g, int (*cmp)(const Goods* a, const Goods* b),int  tag) {	//tag作用为判断使用那种方法打印
	system("cls");
	int res[100];
	int i;
	for (i = 0; i < getGdsLength(g); i++) {
		res[i] = i;
	}
	sort(g, g+getGdsLength(gds)-1, res, cmp);
	if (tag) {	//若为1则打印功能1
		printf("商品编号\t商品类别名称\t商品名称\t库存数量\t单价\t总金额\n");
		for (i = 0; i < getGdsLength(g)-1-1; i++) {
			printf("%s\t%-16s%s\t\t%d\t\t%.2f\t%.2f\n", g[res[i]].gdsNo, g[res[i]].catName, g[res[i]].gdsName, gds[res[i]].stock, g[res[i]].price, (float)g[res[i]].sales * g[res[i]].price);
		}
	}		
	else {		//若为0则打印功能6
		printf("商品编号\t商品名称\t库存数量\t销售数量\t单价\n");
		for (i = 0; i < getGdsLength(g) - 1; i++)
		{
			printf("%5s\t%5s\t\t%5d\t\t%5d\t\t%.2f\n", g[res[i]].gdsNo, g[res[i]].gdsName,
				g[res[i]].stock, g[res[i]].sales, g[res[i]].price);
		}
	}
	system("pause");
}