#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include "depend.h"


/*
	----------------������--------------------
	�������ʱ�ȶ�ȡ���ࡢ��Ʒ�����������ļ���Ȼ���ʼ����Ʒ������
	�ٽ���������֤�����������ȷ����������
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
