#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include "depend.h"


/*
	----------------主函数--------------------
	启动软件时先读取种类、商品、订单三个文件，然后初始化商品销量，
	再进行密码验证，如果密码正确进入主界面
*/
int main(int argc, char *argv[]) {
	readOrder(&order);
	readCat();
	readGds();
	setGds(order);
	pwVerification();
	menu();
	return 0;
}
