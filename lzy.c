#include <stdio.h>
#include "depend.h"

void Selldetail(Goods* goods, const Order p,const Category ki[])
{
	int j=0;
	orderNode *o,*o1,*o2;//����ָ�룬oָ����Ҫ�����Ľڵ㣬o1ָ��o��ǰһ���ڵ㣬o2ָ��o�ĺ�һ���ڵ� 
	o=p;//ָ��oָ������ͷ�� 
	int kin;
	do//����ѭ���ṹ���û��ظ����� 
	{
		system("cls");
		printf("%d.%s\n%d.%s\n%d.%s\n%d.%s\n%d.%s\n%d.%s\n",ki[0].cat, ki[0].catName,ki[1].cat,ki[1].catName,ki[2].cat,ki[2].catName,ki[3].cat,ki[3].catName,ki[4].cat,ki[4].catName,ki[5].cat,ki[5].catName);
	    printf("��������Ҫ��ѯ������ϸ����Ʒ������(����0�������˵�)��");
	    scanf("%d",&kin);
	    if(kin==0)break;
	    if(kin>=1&&kin<=6) 
	    {
	    	system("cls");
	    	printf("������  ��Ʒ���      ��Ʒ����      ��������    ����      �ܽ��\n");
	    	for(;o!=NULL;) //Ѱ����Ҫ�����ಢ��� 
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
	    	printf("ָ��������������룡\n");
	    	system("pause");
	    	continue;
		}
		o=p;
    }while(kin!=0);
	
}


