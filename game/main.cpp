#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"game.h"
using namespace std;

// 三档难度：显示行列数与雷数
static const GameConfig LEVELS[] = {
	{ "初级",  9,  9, 10 },
	{ "中级", 16, 16, 40 },
	{ "高级", 16, 30, 99 },
};
static const int LEVEL_COUNT = 3;

void menu() {
	cout << "---------------------------------\n";
	cout << "  1. 初级    9 x  9    10 雷\n";
	cout << "  2. 中级   16 x 16    40 雷\n";
	cout << "  3. 高级   16 x 30    99 雷\n";
	cout << "  0. 退出\n";
	cout << "---------------------------------\n";
}

// 跑一局，返回 true 表示排雷成功
bool game(const GameConfig& cfg) {
	cout << "\n===== " << cfg.name << " " << cfg.rows << " x " << cfg.cols
		<< "，" << cfg.mines << " 雷 =====\n";

	Board mine, show;//存放雷区、存放显示区
	// 含边界一共 (rows+2) x (cols+2)
	InitBoard(mine, cfg.rows + 2, cfg.cols + 2, '0');
	InitBoard(show, cfg.rows + 2, cfg.cols + 2, '*');

	Displayboard(show, cfg.rows, cfg.cols);
	// 布雷推迟到玩家第一次点击时进行，保证第一下不会踩雷
	return FindMine(mine, show, cfg.rows, cfg.cols, cfg.mines);
}

int main() {
	int input = 0;
	srand((unsigned int)time(NULL));
	do {
		menu();
		cout << "请选择难度：\n";
		cin >> input;
		if (cin.fail()) {
			if (cin.eof()) return 0;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入格式错误，请重新输入\n";
			input = -1;          // 保证 do-while 继续循环，而不是退出
			continue;
		}
		if (input >= 1 && input <= LEVEL_COUNT) {
			game(LEVELS[input - 1]);
		}
		else if (input == 0) {
			cout << "退出游戏\n";
		}
		else {
			cout << "输入错误，请重新输入\n";
		}
	} while (input);
	return 0;
}
