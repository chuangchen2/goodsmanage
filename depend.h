#define True 1
#define False 0
#define SECOND 1000
#define PWMAXSIZE 21
#define MAXSIZE 9

/*---�ṹ�嶨��---*/
typedef struct orderNode* Order;
typedef struct orderNode {
	int orderCode;	//������
	char goodsCode[MAXSIZE];	//��Ʒ���
	int salesVolume;	//����
	float price;	//�۸�
	float totalAmount;	//�ܽ��
	Order next;		//βָ��	
}orderNode;

typedef struct goods {
	char gdsNo[9];     //��Ʒ��� 
	int cat;           //��Ʒ��� 
	char catName[10];  //����� 
	char gdsName[10];  //��Ʒ�� 
	int stock;         //����� 
	float price;       //���� 
	int sales;  //������������ʼֵΪ0�����ݶ������ݸ��£����ڲ�ѯ 
}Goods;
typedef struct category {
	int cat;           //����� 
	char catName[10];  //������	
}Category, category;

/*---ȫ�ֱ���---*/
extern Order order;
extern Goods gds[50];
extern Category gdsCat[10];


void pwVerification();
void menu();
void disGoodsIofo();
void seekCatName(char* s, int cat);
void readOrder(Order* order);
void readCat();
void readGds();
void Selldetail(Goods* goods, const Order p, const Category ki[]);
void setGds(Order List);
int getGdsLength(const Goods* g);
void goodsSort(const Goods* g, int (*cmp)(const Goods* a, const Goods* b), int tag);
void sort(const Goods* begin, const Goods* end, int* res, int (*compar)(const Goods* a, const Goods* b));
int goodsCmp(const Goods* a, const Goods* b);
int goodsSalesCmp(const Goods* a, const Goods* b);
void printGoodsSalesInfo(const Goods* g);