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
	pwVerificationΪ������֤����
	pswordchangeΪ������Ĺ���
	menuΪ�˵�����
	seekgoodsΪ����ĳһ��Ʒ�Ľṹ�ڵ�
	printGoodsΪ���������ĳһ����Ʒ��Ϣ
	printCatΪ������������е���Ʒ������Ϣ
	setGdsΪ����������Ʒ������
	seekCatNameΪ���Ҷ�������
	popOrderListΪ��������������ĳһ������ȫ���ڵ㲢���һ��������
	freeOrderΪ�ͷ�����ڵ�
	pushOrderΪ�ڶ�����������µ���Ϣ
	deleteΪɾ��ĳһ�����ŵ����ж���
	writeOrderΪ���ļ����붩����Ϣ
	writeGoodsΪ���ļ�������Ʒ��Ϣ
	getGdsLengthΪ��ȡGds����ĳ���
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
		temp = _getch();		//ʵ������ʱ��������
		if (temp == '\r') {
			break;
		}
		else if (temp == '\b') {			//ʵ��ɾ���ַ�
			if (i == -1) continue;
			printf("\b \b");
			i--;
			continue;
		}
		else {
			printf("*");//����ʱ��ʾ��*��
			str2[++i] = temp;
		}
	}
	str2[++i] = '\0';
	return str2;
}

void encryp(char* p) {	//�������룬������������ַ���ascii����20
	int i = 0;
	while (*p) {
		*p -= 20;
		p++;
	}
}

void pwVerification() {
	FILE* fp;
	int flag = 3;	//һ�����Գ���������������
	int i;
	char* psword = (char*)calloc(PWMAXSIZE, sizeof(char));
	char* psword2 = (char*)calloc(PWMAXSIZE, sizeof(char));
	if ((fp = fopen("password.dat", "rb")) == NULL) {		//��ȡ����
		if ((fp = fopen("password.dat", "wb")) == NULL) {
			printf("�޷��������룬�����˳�ϵͳ");
			Sleep(2 * SECOND);
			exit(1);
		}
		else {
			while (True) {
				printf("ϵͳδ�������룬�����������루���20���ַ���:");
				psword = pswordInput(psword);
				printf("\n�ٴ�����������:");
				psword2 = pswordInput(psword2);
				if (strcmp(psword, psword2) == 0) {	//�����������һ�£���������벢д���ļ����˳�����
					printf("\n���óɹ������ڽ���ϵͳ");
					encryp(psword);
					fwrite(psword, sizeof(char), 21, fp);
					Sleep(SECOND);
					free(psword);	//�ͷ������ַ����Ŀռ�
					free(psword2);
					fclose(fp);
					return;
				}
				else {
					printf("���벻һ�£�����������\n");
				}
			}
		}

	}
	else {
		i = -1;
		if (fread(psword, sizeof(char), 21, fp) && psword[0] == '0') {
			printf("��ȡ����ʧ��\n");
		}
		while (flag) {
			printf("���������룺");
			psword2 = pswordInput(psword2);
			encryp(psword2);
			if (strcmp(psword, psword2) == 0) {	//��������ȷ���˳�������˳�����
				printf("\n������ȷ�����ڽ���ϵͳ\n");
				Sleep(SECOND);//���ֹͣһ��
				free(psword);
				free(psword2);
				fclose(fp);
				return;
			}
			else {
				flag--;	//������һ
				if (flag != 0)		//�������������󳬹��������˳�����
					printf("\n����������󣬻���%d�λ���\n", flag);
				else {
					printf("\n���Դ��������꣬�����˳�ϵͳ");
					Sleep(SECOND);
				}

			}
		}
		exit(2);	//�����Դ���Ϊ0���˳�ϵͳ
	}
}

void menu() {
	while (True) {
		int index;
		system("cls");//��shell��ȫ������Ϣ���
		printf("\n\n****************************************************��Ʒ����ϵͳ�˵�****************************************************\n");
		printf("\n\n\n");
		printf("%s============================\n",SPACESIZE);
		printf("%s1. ����Ʒ�������\n",SPACESIZE);
		printf("%s2. ������Ʒ\n",SPACESIZE);
		printf("%s3. ɾ��ָ������\n", SPACESIZE);
		printf("%s4. ����������Ʒ������ϸ\n", SPACESIZE);
		printf("%s5. ������Ʒ�������ͳ��\n", SPACESIZE);
		printf("%s6. ����Ʒ����������\n", SPACESIZE);
		printf("%s7. ���ָ����Ʒ��Ϣ\n", SPACESIZE);
		printf("%s8. �޸�����\n", SPACESIZE);
		printf("%s0. �˳�ϵͳ\n", SPACESIZE);
		printf("%s============================\n", SPACESIZE);
		printf("%s��ѡ��", SPACESIZE);

		scanf("%d", &index);
		switch (index) {//ѡ����
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
		case 0:		//��ѡ���˳�ϵͳ������������Ʒ����Ϣд���ļ����˳�
			writeGoods();
			writeOrder();
			exit(0);
		default:
			printf("\t\t\t\t\t    �����������������!");
			Sleep(SECOND/2);//���ֹͣ���������
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
		printf("\n\n****************************************************��Ʒ����ϵͳ�˵�****************************************************\n\n\n\n");
		printf("%s������������:", SPACESIZE);
		psw = pswordInput(psw);
		printf("\n%s�ٴ�����������:", SPACESIZE);
		psw2 = pswordInput(psw2);
		if (strcmp(psw, psw2) == 0) {	//����ʵ��ͬ��ʼ�����뺯��
			encryp(psw);
			fwrite(psw, sizeof(char), 21, fp);
			printf("\n%s�޸ĳɹ���", SPACESIZE);
			break;
		}
		else {
			printf("%s������������벻ͬ������������", SPACESIZE);
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
		���½�һ���սڵ�Ϊ�����ͷ�ڵ㣬Ȼ������ļ���ע�Ͳ�����������ȫ���ַ���
		Ȼ����ò��뺯����һ���ļ���ȫ��������Ϣ���뵽������
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
		printf("�ļ� order.txt ��ʧ�ܣ������˳�ϵͳ");
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
		����������Ʒ������Ϣ�����浽gdsCat�����У�����������������ż�Ϊ0��ʾ�������
	*/
	FILE* fp;
	char buf[100];
	int i = 0;
	if ((fp = fopen("category.txt", "r")) == NULL) {
		printf("�ļ� category.txt ��ʧ�ܣ������˳�ϵͳ");
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
			����������Ʒ��Ϣ�����浽gds�����У�����������������ż�Ϊ0��ʾ���������������seekCatName���������������Ʋ�����
	*/
	FILE* fp;
	int i = 0;
	if ((fp = fopen("goods.txt", "r")) == NULL) {
		printf("�ļ� goods.txt ��ʧ�ܣ������˳�ϵͳ");
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
		if (gdsCat[i].cat == cat) {		//������һ�£���д������
			strcpy(s, gdsCat[i].catName);
			break;
		}
		++i;
	}
}

void pushOrder(Order* prev, int orderCode, char* goodsCode, int salesVolume, float price, float totalAmount, Order next) {
	Order this = (Order)malloc(sizeof(struct orderNode));	//�½�һ���ڵ㲢����Ϣд�룬���뵽����ָ��֮�󣬲���ָ���ƶ����½ڵ���
	this->orderCode = orderCode;
	strcpy(this->goodsCode, goodsCode);
	this->salesVolume = salesVolume;
	this->price = price;
	this->totalAmount = totalAmount;
	this->next = next;
	(*prev)->next = this;//�ƶ�ָ��
	(*prev) = this;

}

Order popOrderList(int orderCode, Order orderList) {
	//�½�һ���սڵ�Ϊ�������ͷ�ڵ㣬����pop�Ľڵ㴮��ͷ�ڵ�󣬲���β�ڵ��βָ��ָ��NULL������ͷ�ڵ��ָ��
	Order head = (Order)malloc(sizeof(struct orderNode));
	Order prve = orderList;
	Order next;
	Order _next;
	while (prve != NULL) {
		next = prve->next;
		_next = next;
		if (next->orderCode == orderCode) {//����ҵ�Ŀ�궩������prveͣ����next��ǰһλ��nextָ��Ŀ�궩���ĵ�һ���ڵ�
			head->next = next;
			while (next->next != NULL) {
				next = next->next;
				if (next->orderCode != orderCode) {//���ҵ���һ����Ŀ�궩����һ���Ķ�������nextͣ������Ϊ���Ա㴦�������
					_next->next = NULL;//�������βָ��ָ��NULL
					break;
				}
				_next = next;//���������_next�����ƶ�
			}
			if (next->next != NULL) {
				prve->next = next;//Ȼ��prve��βָ��ָ��next
				break;
			}
			else {
				prve->next = NULL;
				break;
			}
		}
		prve = next;//������Ŀ�궩������prve�ƶ���next��
	}
	return head;
}

void printOrder(Order order) {
	printf("�������\t��Ʒ���\t������\t����\t�ܽ��\n");
	while (order->next != NULL) {
		order = order->next;
		printf("%04d\t\t%s\t%d\t%.1f\t%.1f\n", order->orderCode, order->goodsCode, order->salesVolume, order->price, order->totalAmount);
	}
}

void freeOrder(Order List) {
	Order next;
	while (List->next != NULL) {//��һ�ͷŽڵ�ֱ������Ϊ��
		next = List->next;
		free(List);
		List = next;
	}
	free(List);
}

void updateGds(char* goodsCode, int salesVolume) {
	/*
		�������������������������һ���ϣ����������Ʒ�������ĳ�ʼ��	
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
	printOrder(order);	//�ȴ�ӡ�����ж�������Ϣ�������û�ѡ��
	printf("��ѡ������Ҫɾ���Ķ���������0ȡ����������");
	if (scanf("%d", &num) && (num == 0)) {
		return;
	}
	printf("ȷ���Ƿ�ɾ��%04d�Ŷ�����1ȷ��ɾ����0ȡ��ɾ������", num);
	scanf("%d", &flag);
	if (flag == 1) {
		List = popOrderList(num, order);//��Ҫɾ���Ķ�������
		printf("���¶�����ɾ����\n");
		printOrder(List);	//��ӡ����ɾ���Ķ���
		setGds(List);	//����������Ʒ����
		freeOrder(List);	//�ͷ�ɾ����������Ľڵ�
		printf("��ɾ��%04d�Ŷ���\n", num);
	}
	else {
		printf("��ȡ��ɾ��\n");
	}
	system("pause");	//ֹͣ����ֱ���û��������ⰴ�����˳�����
	return;
}

void salesGoods(Order o) {
	/*
		�ȶ�������ͷ�ڵ㣬���û�ѡ����Ʒ���࣬����ʾ���������ȫ����Ʒ���û�ѡȡ��
		���û���������󣬽���Ϣ��������
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
		printf("��ѡ����Ʒ���ͣ�����0��������");
		if (scanf("%d", &flag) && (flag == 0)) {
			return;
		}
		printGoods(gds,flag);
		printf("��ѡ����Ʒ��ţ�");
		scanf("%s", goodsCode);
		goods = seekgoods(goodsCode);
		printf("�����빺��������");
		scanf("%d", &num);
		if (goods->stock - num < 0) {	//��������������棬��ȡ���ò���
			printf("�����������������\n");
			system("pause");
		}
		else {
			goods->stock -= num;
			pushOrder(&next, index, goodsCode, num, goods->price, goods->price * num, NULL);
			goods->sales += num;
			printf("�����ɹ���");
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
	printf("�����\t�����\n");
	for (i = 0; gdsCat[i].cat != 0; i++) {
		printf("%d\t\t%s\n", gdsCat[i].cat, gdsCat[i].catName);
	}
	return;
}

void printGoods(const Goods* gds ,int cat) {
	int i;
	printf("��Ʒ���\t��Ʒ����\n");
	for (i = 0; strcmp(gds[i].gdsNo, "0") != 0; i++) {
		if (gds[i].cat == cat) {
			printf("%s\t%s\n", gds[i].gdsNo, gds[i].gdsName);
		}
	}
	return;
}

void writeOrder() {
	/*����������д���ļ�*/
	FILE* fp;
	Order next = order;
	if ( (fp = fopen("order.txt", "w")) == NULL) {
		printf("�ļ� order.txt д��ʧ�ܣ�");
		exit(3);
	}
	else {
		fputs(goodsStr1, fp);//�Ƚ�ע��д���д������
		fputs(goodsStr2, fp);
		while (next->next != NULL){
			next = next->next;
			fprintf(fp, "%04d %s %d %.1f %.1f\n", next->orderCode, next->goodsCode, next->salesVolume, next->price, next->totalAmount);
		}
		fclose(fp);
	}
}

void writeGoods() {
	/*����Ʒ��Ϣд�뵽�ļ�*/
	FILE* fp;
	if ( (fp = fopen("goods.txt", "w")) == NULL) {
		printf("�ļ� goods.txt д��ʧ�ܣ�");
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
	while (g->gdsNo[0] != '0') {	//��gdsNOΪ������׼������ѭ�����˳�����
		g++;
		res++;
	}
	return res;
}