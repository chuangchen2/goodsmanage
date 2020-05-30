#define True 1
#define False 0
#define SECOND 1000
#define PWMAXSIZE 21
#define MAXSIZE 9

/*---结构体定义---*/
typedef struct orderNode* Order;
typedef struct orderNode {
	int orderCode;	//订单号
	char goodsCode[MAXSIZE];	//商品编号
	int salesVolume;	//销量
	float price;	//价格
	float totalAmount;	//总金额
	Order next;		//尾指针	
}orderNode;

typedef struct goods {
	char gdsNo[9];     //商品编号 
	int cat;           //商品类别 
	char catName[10];  //类别名 
	char gdsName[10];  //商品名 
	int stock;         //库存量 
	float price;       //单价 
	int sales;  //销售数量，初始值为0，根据订单数据更新，便于查询 
}Goods;
typedef struct category {
	int cat;           //分类号 
	char catName[10];  //分类名	
}Category, category;

/*---全局变量---*/
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