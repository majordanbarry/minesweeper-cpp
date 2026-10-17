#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"game.h"
using namespace std;
void menu() {
	cout << "-----------------\n";
	cout << "------1.play-----\n";
	cout << "------0.exit-----\n";
	cout << "-----------------\n";
}
void game() {
	cout << "扫雷开始" << endl;
	char mine[ROWS][COLS] = {};//存放雷区
	char show[ROWS][COLS] = {};//存放显示区
	InitBoard(mine, ROWS, COLS,'0');
	InitBoard(show, ROWS, COLS,'*');
	Displayboard(show, ROW, COL);
	SetMine(mine, ROW, COL);
	FindMine(mine, show, ROW, COL);
}
int main(){
	int input = 0;
	srand((unsigned int)time(NULL));
	do {
		menu();
		cout << "请选择游戏模式：\n";
		cin >> input;
		switch (input) {
			case 1:
				cout << "开始游戏" << endl;
				game();
				break;
			case 0:
				cout << "退出游戏" << endl;
				break;
			default:
				cout << "输入错误，请重新输入" << endl;
				break;
		}
	} while (input);
	return 0;
}

	