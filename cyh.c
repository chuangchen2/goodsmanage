#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include "depend.h"

const char* SPACESIZE = "\t\t\t\t\t     ";
char orderStr1[100];
char orderStr2[100];
char goodsStr1[100];
char goodsStr2[100];
Order order;
Goods gds[50];
Category gdsCat[10];

/*
	pwVerification为密码验证功能
	pswordchange为密码更改功能
	menu为菜单功能
	seekgoods为查找某一商品的结构节点
	printGoods为遍历并输出某一种商品信息
	printCat为遍历并输出所有的商品种类信息
	setGds为设置所有商品的销量
	seekCatName为查找订单名称
	popOrderList为弹出订单链表中某一订单的全部节点并组成一条新链表
	freeOrder为释放链表节点
	pushOrder为在订单链表插入新的信息
	delete为删除某一订单号的所有订单
	writeOrder为从文件读入订单信息
	writeGoods为从文件读入商品信息
	getGdsLength为获取Gds数组的长度
*/

void pwVerification();
void pswordchange();
void menu();
Goods* seekgoods(char* gooodsCode);
void salesGoods(Order o);
void printGoods(const Goods* gds, int cat);
void printCat(const Category* cat);
void setGds(Order order);
void seekCatName(char* s, int cat);
Order popOrderList(int orderCode, Order orderList);
void freeOrder(Order List);
void pushOrder(Order* prev, int orderCode, char* goodsCode, int salesVolume, float price, float totalAmount, Order next);
void deleteOrder(Order order);
void writeOrder();
void writeGoods();
int getGdsLength(const Goods* g);

char* pswordInput(char* str) {
	int i = -1;
	char temp;
	char* str2 = str;
	while (i != 20) {
		temp = _getch();		//实现输入时隐藏密码
		if (temp == '\r') {
			break;
		}
		else if (temp == '\b') {			//实现删除字符
			if (i == -1) continue;
			printf("\b \b");
			i--;
			continue;
		}
		else {
			printf("*");//输入时显示‘*’
			str2[++i] = temp;
		}
	}
	str2[++i] = '\0';
	return str2;
}

void encryp(char* p) {	//加密密码，将密码的所有字符的ascii减少20
	int i = 0;
	while (*p) {
		*p -= 20;
		p++;
	}
}

void pwVerification() {
	FILE* fp;
	int flag = 3;	//一共可以尝试输入三次密码
	int i;
	char* psword = (char*)calloc(PWMAXSIZE, sizeof(char));
	char* psword2 = (char*)calloc(PWMAXSIZE, sizeof(char));
	if ((fp = fopen("password.dat", "rb")) == NULL) {		//读取密码
		if ((fp = fopen("password.dat", "wb")) == NULL) {
			printf("无法设置密码，即将退出系统");
			Sleep(2 * SECOND);
			exit(1);
		}
		else {
			while (True) {
				printf("系统未设置密码，请先设置密码（最多20个字符）:");
				psword = pswordInput(psword);
				printf("\n再次输入新密码:");
				psword2 = pswordInput(psword2);
				if (strcmp(psword, psword2) == 0) {	//如果密码输入一致，则加密密码并写入文件后退出函数
					printf("\n设置成功，正在进入系统");
					encryp(psword);
					fwrite(psword, sizeof(char), 21, fp);
					Sleep(SECOND);
					free(psword);	//释放两个字符串的空间
					free(psword2);
					fclose(fp);
					return;
				}
				else {
					printf("密码不一致，请重新输入\n");
				}
			}
		}

	}
	else {
		i = -1;
		if (fread(psword, sizeof(char), 21, fp) && psword[0] == '0') {
			printf("读取密码失败\n");
		}
		while (flag) {
			printf("请输入密码：");
			psword2 = pswordInput(psword2);
			encryp(psword2);
			if (strcmp(psword, psword2) == 0) {	//若密码正确则退出密码后退出函数
				printf("\n密码正确，正在进入系统\n");
				Sleep(SECOND);//软件停止一秒
				free(psword);
				free(psword2);
				fclose(fp);
				return;
			}
			else {
				flag--;	//次数减一
				if (flag != 0)		//如果输入密码错误超过三次则退出程序
					printf("\n密码输入错误，还有%d次机会\n", flag);
				else {
					printf("\n尝试次数已用完，正在退出系统");
					Sleep(SECOND);
				}

			}
		}
		exit(2);	//若尝试次数为0后，退出系统
	}
}

void menu() {
	while (True) {
		int index;
		system("cls");//将shell的全部信信息清除
		printf("\n\n****************************************************商品销售系统菜单****************************************************\n");
		printf("\n\n\n");
		printf("%s============================\n",SPACESIZE);
		printf("%s1. 按商品编号排序\n",SPACESIZE);
		printf("%s2. 销售商品\n",SPACESIZE);
		printf("%s3. 删除指定订单\n", SPACESIZE);
		printf("%s4. 给定类别的商品销售明细\n", SPACESIZE);
		printf("%s5. 所有商品销售情况统计\n", SPACESIZE);
		printf("%s6. 按商品销售量排序\n", SPACESIZE);
		printf("%s7. 输出指定商品信息\n", SPACESIZE);
		printf("%s8. 修改密码\n", SPACESIZE);
		printf("%s0. 退出系统\n", SPACESIZE);
		printf("%s============================\n", SPACESIZE);
		printf("%s请选择：", SPACESIZE);

		scanf("%d", &index);
		switch (index) {//选择功能
		case 1:
			goodsSort(gds,goodsCmp, 1); break;
		case 2:
			salesGoods(order); break;
		case 3:
			deleteOrder(order); break;
		case 4:
			Selldetail(gds, order, gdsCat); break;
		case 5:
			printGoodsSalesInfo(gds); break;
		case 6:
			goodsSort(gds, goodsSalesCmp, 0); break;
		case 7:
			disGoodsIofo(); break;
		case 8:
			pswordchange(); break;
		case 0:		//若选择退出系统，将订单和商品的信息写入文件后退出
			writeGoods();
			writeOrder();
			exit(0);
		default:
			printf("\t\t\t\t\t    输出错误，请重新输入!");
			Sleep(SECOND/2);//软件停止半秒后清屏
			break;
		}
	}
}

void pswordchange() {
	system("cls");
	FILE* fp;
	char* psw = (char*)calloc(PWMAXSIZE, sizeof(char));
	char* psw2 = (char*)calloc(PWMAXSIZE, sizeof(char));
	fp = fopen("password.dat", "wb");
	while (True) {
		system("cls");
		printf("\n\n****************************************************商品销售系统菜单****************************************************\n\n\n\n");
		printf("%s请输入新密码:", SPACESIZE);
		psw = pswordInput(psw);
		printf("\n%s再次输入新密码:", SPACESIZE);
		psw2 = pswordInput(psw2);
		if (strcmp(psw, psw2) == 0) {	//具体实现同初始化密码函数
			encryp(psw);
			fwrite(psw, sizeof(char), 21, fp);
			printf("\n%s修改成功！", SPACESIZE);
			break;
		}
		else {
			printf("%s两次输入的密码不同，请重新输入", SPACESIZE);
		}
	}
	fclose(fp);
	free(psw2);
	free(psw);
	Sleep(2 * SECOND);
	return;
}

void readOrder(Order* order) {
	/*
		先新建一个空节点为链表的头节点，然后读入文件的注释并保存在两个全局字符串
		然后调用插入函数逐一将文件的全部订单信息插入到链表中
	*/
	*order = (Order)malloc(sizeof(struct orderNode));
	Order next = *order;
	FILE* fp;
	int orderCode;
	char goodsCode[MAXSIZE];
	int salesVolume = 0;
	float price = 0;
	float totalAmount = 0;
	if ((fp = fopen("order.txt", "r+")) == NULL) {
		printf("文件 order.txt 打开失败，即将退出系统");
		exit(3);
	}
	else {
		fgets(orderStr1, 100, fp);
		fgets(orderStr2, 100, fp);
		while (feof(fp) == 0) {
			fscanf(fp, "%d %s %d %f %f", &orderCode, goodsCode, &salesVolume, &price, &totalAmount);
			pushOrder(&next, orderCode, goodsCode, salesVolume, price, totalAmount, NULL);
		}
	}
}

void readCat() {
	/*
		读入所有商品种类信息并保存到gdsCat数组中，并将数组最后的种类号记为0表示数组结束
	*/
	FILE* fp;
	char buf[100];
	int i = 0;
	if ((fp = fopen("category.txt", "r")) == NULL) {
		printf("文件 category.txt 打开失败，即将退出系统");
		exit(4);
	}
	else {
		fgets(buf, 100, fp);
		fgets(buf, 100, fp);
		while (feof(fp) == 0) {
			fscanf(fp, "%d %s", &gdsCat[i].cat, gdsCat[i].catName);
			++i;
		}
		gdsCat[i].cat = 0;
		fclose(fp);
	}
	return;
}

void readGds() {
	/*
			读入所有商品信息并保存到gds数组中，并将数组最后的种类号记为0表示数组结束，并调用seekCatName函数查找种类名称并保存
	*/
	FILE* fp;
	int i = 0;
	if ((fp = fopen("goods.txt", "r")) == NULL) {
		printf("文件 goods.txt 打开失败，即将退出系统");
		exit(5);
	}
	else {
		fgets(goodsStr1, 100, fp);  
		fgets(goodsStr2, 100, fp);
		while (feof(fp) == 0) {
			fscanf(fp, "%s%d%s%d%f", gds[i].gdsNo, &gds[i].cat, gds[i].gdsName, &gds[i].stock, &gds[i].price);
			gds[i].sales = 0;
			seekCatName(gds[i].catName, gds[i].cat);
			++i;
		}
		strcpy(gds[i].gdsNo, "0");
		fclose(fp);
	}
	return;
}

void seekCatName(char* s, int cat) {  
	int i = 0;
	while (gdsCat[i].cat != 0) {
		if (gdsCat[i].cat == cat) {		//如果标号一致，则写入数组
			strcpy(s, gdsCat[i].catName);
			break;
		}
		++i;
	}
}

void pushOrder(Order* prev, int orderCode, char* goodsCode, int salesVolume, float price, float totalAmount, Order next) {
	Order this = (Order)malloc(sizeof(struct orderNode));	//新建一个节点并将信息写入，插入到传入指针之后，并将指针移动到新节点上
	this->orderCode = orderCode;
	strcpy(this->goodsCode, goodsCode);
	this->salesVolume = salesVolume;
	this->price = price;
	this->totalAmount = totalAmount;
	this->next = next;
	(*prev)->next = this;//移动指针
	(*prev) = this;

}

Order popOrderList(int orderCode, Order orderList) {
	//新建一个空节点为新链表的头节点，后将想pop的节点串到头节点后，并将尾节点的尾指针指向NULL，返回头节点的指针
	Order head = (Order)malloc(sizeof(struct orderNode));
	Order prve = orderList;
	Order next;
	Order _next;
	while (prve != NULL) {
		next = prve->next;
		_next = next;
		if (next->orderCode == orderCode) {//如果找到目标订单，将prve停留在next的前一位，next指向目标订单的第一个节点
			head->next = next;
			while (next->next != NULL) {
				next = next->next;
				if (next->orderCode != orderCode) {//若找到第一个与目标订单不一样的订单，则将next停留在这为，以便处理就链表
					_next->next = NULL;//新链表的尾指针指向NULL
					break;
				}
				_next = next;//如果不是则_next往后移动
			}
			if (next->next != NULL) {
				prve->next = next;//然后将prve的尾指针指向next
				break;
			}
			else {
				prve->next = NULL;
				break;
			}
		}
		prve = next;//若不是目标订单，则prve移动到next处
	}
	return head;
}

void printOrder(Order order) {
	printf("订单编号\t商品编号\t销售量\t单价\t总金额\n");
	while (order->next != NULL) {
		order = order->next;
		printf("%04d\t\t%s\t%d\t%.1f\t%.1f\n", order->orderCode, order->goodsCode, order->salesVolume, order->price, order->totalAmount);
	}
}

void freeOrder(Order List) {
	Order next;
	while (List->next != NULL) {//逐一释放节点直到链表为空
		next = List->next;
		free(List);
		List = next;
	}
	free(List);
}

void updateGds(char* goodsCode, int salesVolume) {
	/*
		遍历订单链表，如果将其销量逐一加上，完成所有商品的销量的初始化	
	*/
	int i = 0;
	while (strcmp(gds[i].gdsNo, "0")) {
		if (strcmp(gds[i].gdsNo, goodsCode) == 0) {
			gds[i].sales += salesVolume;
			break;
		}
		i++;
	}
}

void setGds(Order List) {
	while (List != NULL) {
		updateGds(List->goodsCode, List->salesVolume);
		List = List->next;
	}
}

void deleteOrder(Order order) {
	system("cls");
	int num = 0;
	int flag;
	Order List;
	printOrder(order);	//先打印出所有订单的信息，后让用户选择
	printf("请选择你想要删除的订单（输入0取消操作）：");
	if (scanf("%d", &num) && (num == 0)) {
		return;
	}
	printf("确认是否删除%04d号订单（1确认删除，0取消删除）：", num);
	scanf("%d", &flag);
	if (flag == 1) {
		List = popOrderList(num, order);//将要删除的订单弹出
		printf("以下订单已删除：\n");
		printOrder(List);	//打印出已删除的订单
		setGds(List);	//重新设置商品销量
		freeOrder(List);	//释放删除订单链表的节点
		printf("已删除%04d号订单\n", num);
	}
	else {
		printf("已取消删除\n");
	}
	system("pause");	//停止程序，直到用户按下任意按键后退出函数
	return;
}

void salesGoods(Order o) {
	/*
		先读入链表头节点，让用户选择商品种类，后显示出该种类的全部商品让用户选取，
		待用户结束输入后，将信息插入链表
	*/
	int index = 0;
	int flag = 0;
	int num = 0;
	Goods* goods;
	char goodsCode[MAXSIZE];
	Order next;
	next = o;
	while (next->next != NULL) {
		next = next->next;
	}
	index = next->orderCode + 1;
	while (True) {
		system("cls");
		printCat(gdsCat);
		printf("请选择商品类型（输入0结束）：");
		if (scanf("%d", &flag) && (flag == 0)) {
			return;
		}
		printGoods(gds,flag);
		printf("请选择商品编号：");
		scanf("%s", goodsCode);
		goods = seekgoods(goodsCode);
		printf("请输入购买数量：");
		scanf("%d", &num);
		if (goods->stock - num < 0) {	//若销售量超过库存，则取消该操作
			printf("销售量超过库存量！\n");
			system("pause");
		}
		else {
			goods->stock -= num;
			pushOrder(&next, index, goodsCode, num, goods->price, goods->price * num, NULL);
			goods->sales += num;
			printf("操作成功！");
			system("pause");
		}
	}
}

Goods* seekgoods(char* gooodsCode) {
	int i;
	for (i = 0; strcmp(gds[i].gdsNo, "0") != 0; i++) {
		if (strcmp(gooodsCode, gds[i].gdsNo) == 0)
		{
			return &gds[i];
		}
	}
	return NULL;
}

void printCat(const Category* cat) {
	int i;
	printf("类别编号\t类别名\n");
	for (i = 0; gdsCat[i].cat != 0; i++) {
		printf("%d\t\t%s\n", gdsCat[i].cat, gdsCat[i].catName);
	}
	return;
}

void printGoods(const Goods* gds ,int cat) {
	int i;
	printf("商品编号\t商品名称\n");
	for (i = 0; strcmp(gds[i].gdsNo, "0") != 0; i++) {
		if (gds[i].cat == cat) {
			printf("%s\t%s\n", gds[i].gdsNo, gds[i].gdsName);
		}
	}
	return;
}

void writeOrder() {
	/*将订单链表写入文件*/
	FILE* fp;
	Order next = order;
	if ( (fp = fopen("order.txt", "w")) == NULL) {
		printf("文件 order.txt 写入失败！");
		exit(3);
	}
	else {
		fputs(goodsStr1, fp);//先将注释写入后写入数据
		fputs(goodsStr2, fp);
		while (next->next != NULL){
			next = next->next;
			fprintf(fp, "%04d %s %d %.1f %.1f\n", next->orderCode, next->goodsCode, next->salesVolume, next->price, next->totalAmount);
		}
		fclose(fp);
	}
}

void writeGoods() {
	/*将商品信息写入到文件*/
	FILE* fp;
	if ( (fp = fopen("goods.txt", "w")) == NULL) {
		printf("文件 goods.txt 写入失败！");
		exit(3);
	}
	else {
		fputs(goodsStr1, fp);
		fputs(goodsStr2, fp);
		int i = 0;
		while (strcmp(gds[i].gdsNo, "0")) {
			fprintf(fp, "%s %d %s %d %.2f\n", gds[i].gdsNo, gds[i].cat, gds[i].gdsName, gds[i].stock, gds[i].price);
			i++;
		}
		fclose(fp);
	}
}

int getGdsLength(const Goods* g) {
	int res = 0;
	while (g->gdsNo[0] != '0') {	//若gdsNO为结束标准，跳出循环并退出函数
		g++;
		res++;
	}
	return res;
}