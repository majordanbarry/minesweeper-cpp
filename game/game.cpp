#define _CRT_SECURE_NO_WARNINGS
#include"game.h"

void InitBoard(char board[ROWS][COLS], int r, int c,char set) {
	for (int i = 0;i < r;i++) {
		for (int j = 0;j < c;j++) {
				board[i][j] = set;
		}
	}
}
void Displayboard(char board[ROWS][COLS], int r, int c) {
	cout << "  ";
	for (int i = 1;i <= c;i++) {
		cout << i << " ";//打印列序号
	}
	cout << "\n";
	for (int i = 1;i <= r;i++) {
		cout << i << " ";//打印行序号
		for (int j = 1;j <= c;j++) {
			cout<<board[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout << "\n";
}
void SetMine(char mine[ROWS][COLS], int r, int c) {
	int count = easy_count;
	while (count) {
		int x = rand() % r + 1;
		int y = rand() % c + 1;
		if (mine[x][y] == '0') {
			mine[x][y] = '1';
			count--;
		}
		
	}
}
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c) {
	int x = 0, y = 0;
	int win = 0;
	while(win<r*c- easy_count) {
		cout << "请输入排查雷的坐标：\n";
		cin >> x >> y;
		if (cin.fail()) {
			if (cin.eof()) return;                                    // 输入流结束，直接退出本局
			cin.clear();                                             // 清除失败状态
			cin.ignore(numeric_limits<streamsize>::max(), '\n');     // 丢弃这一行坏输入
			cout << "输入格式错误，请输入两个数字！\n";
			continue;
		}
		if (x >= 1 && x <= r && y >= 1 && y <= c) {
			if (show[x][y] != '*') {
				cout << "该位置已排查过，请重新输入！\n";
				continue;
			}
			if (mine[x][y] == '1') {
				cout << "很遗憾，你踩到雷了！\n";
				Displayboard(mine, r, c);
				return;
			}
			else {
				win += OpenBoard(mine, show, x, y);
				Displayboard(show, r, c);
			}
		}
		else {
			cout << "输入的坐标不合法，请重新输入！\n";
		}
		if(win== r * c - easy_count)
			cout << "恭喜你，排雷成功！\n";
	}

}
int OpenBoard(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y) {
	// 1. 越界 → 不处理（continue 的等价物：直接返回 0）
	if (x < 1 || x > ROW || y < 1 || y > COL) return 0;

	// 2. 已翻开 → 不处理（这就是"已访问"标记）
	if (show[x][y] != '*') return 0;

	// 3. 翻开自己
	int count = GetMineCount(mine, x, y);
	show[x][y] = count + '0';
	int opened = 1;

	// 4. 周围无雷才向邻居扩散
	if (count == 0) {
		for (int i = x - 1; i <= x + 1; i++) {
			for (int j = y - 1; j <= y + 1; j++) {
				opened += OpenBoard(mine, show, i, j);
			}
		}
	}
	return opened;
}

int GetMineCount(char mine[ROWS][COLS], int r, int c) {
		int count = 0;
		for (int i = r - 1;i <= r + 1;i++) {
			for (int j = c - 1;j <= c + 1;j++) {
				if (mine[i][j] == '1') {
					count++;
				}
			}
		}
		return count;
	}
//mine数组里的1表示有雷，0表示没有雷
//show数组里的*表示未翻开，数字表示周围雷的数量
//11行11列均填入数据，但仅显示9行9列，边界行列用于计算周围雷的数量
//初始化-布置雷-排查雷