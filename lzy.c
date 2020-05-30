#include <stdio.h>
#include "depend.h"

void Selldetail(Goods* goods, const Order p,const Category ki[])
{
	int j=0;
	orderNode *o,*o1,*o2;//定义指针，o指向需要操作的节点，o1指向o的前一个节点，o2指向o的后一个节点 
	o=p;//指针o指向链表头部 
	int kin;
	do//建立循环结构供用户重复操作 
	{
		system("cls");
		printf("%d.%s\n%d.%s\n%d.%s\n%d.%s\n%d.%s\n%d.%s\n",ki[0].cat, ki[0].catName,ki[1].cat,ki[1].catName,ki[2].cat,ki[2].catName,ki[3].cat,ki[3].catName,ki[4].cat,ki[4].catName,ki[5].cat,ki[5].catName);
	    printf("请输入您要查询销售明细的商品的种类(输入0返回主菜单)：");
	    scanf("%d",&kin);
	    if(kin==0)break;
	    if(kin>=1&&kin<=6) 
	    {
	    	system("cls");
	    	printf("订单号  商品编号      商品名称      销售数量    单价      总金额\n");
	    	for(;o!=NULL;) //寻找需要的种类并输出 
	    	{
	    		int n=0;
	    		for(n;goods[n].gdsNo[0]!='0';n++)
	    		{
	    			if(strcmp(goods[n].gdsNo,o->goodsCode)==0)break;
				}
				if(goods[n].cat!=kin)
				{
					o=o->next;
					continue;
				}
				printf("%04d%12s%12s%12d%12.2f%12.2f\n",o->orderCode,o->goodsCode,goods[n].gdsName,o->salesVolume,o->price,o->totalAmount);
				o=o->next;
			}
			system("pause");
		}
	    else
	    {
	    	system("cls");
	    	printf("指令错误，请重新输入！\n");
	    	system("pause");
	    	continue;
		}
		o=p;
    }while(kin!=0);
	
}


