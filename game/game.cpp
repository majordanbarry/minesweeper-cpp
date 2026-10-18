#define _CRT_SECURE_NO_WARNINGS
#include"game.h"

void InitBoard(Board& board, int totalR, int totalC, char set) {
	board.assign(totalR, vector<char>(totalC, set));
}

void Displayboard(const Board& board, int r, int c) {
	cout << string(CELL_W, ' ');
	for (int i = 1;i <= c;i++) {
		cout << setw(CELL_W) << i;//打印列序号
	}
	cout << "\n";
	for (int i = 1;i <= r;i++) {
		cout << setw(CELL_W) << i;//打印行序号
		for (int j = 1;j <= c;j++) {
			cout << setw(CELL_W) << board[i][j];
		}
		cout << "\n";
	}
	cout << "\n";
}

// 游戏结束时的揭晓视图：雷显示 #，没翻开的空地显示 .，翻开的显示数字
void DisplayResult(const Board& mine, const Board& show, int r, int c) {
	cout << string(CELL_W, ' ');
	for (int i = 1;i <= c;i++) {
		cout << setw(CELL_W) << i;//打印列序号
	}
	cout << "\n";
	for (int i = 1;i <= r;i++) {
		cout << setw(CELL_W) << i;//打印行序号
		for (int j = 1;j <= c;j++) {
			if (mine[i][j] == '1') {
				cout << setw(CELL_W) << "#";   // 雷
			}
			else if (show[i][j] == '*') {
				cout << setw(CELL_W) << ".";   // 没翻开的空地
			}
			else {
				cout << setw(CELL_W) << show[i][j]; // 已翻开的格子（数字）
			}
		}
		cout << "\n";
	}
	cout << "\n";
}

// 布雷：避开首次点击点周围的 3x3 区域，保证第一下不会踩雷
void SetMine(Board& mine, int r, int c, int mineCount, int safeX, int safeY) {
	int count = mineCount;
	while (count > 0) {
		int x = rand() % r + 1;
		int y = rand() % c + 1;
		// 落在安全区（首次点击点及其周围 8 格）就重新抽一次
		if (x >= safeX - 1 && x <= safeX + 1 && y >= safeY - 1 && y <= safeY + 1) continue;
		if (mine[x][y] == '0') {
			mine[x][y] = '1';
			count--;
		}
	}
}

int GetMineCount(const Board& mine, int r, int c) {
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

int OpenBoard(const Board& mine, Board& show, int r, int c, int x, int y) {
	// 1. 越界 → 不处理（continue 的等价物：直接返回 0）
	if (x < 1 || x > r || y < 1 || y > c) return 0;

	// 2. 已翻开 → 不处理（这就是"已访问"标记）
	if (show[x][y] != '*') return 0;

	// 3. 翻开自己
	int count = GetMineCount(mine, x, y);
	show[x][y] = (char)(count + '0');
	int opened = 1;

	// 4. 周围无雷才向邻居扩散
	if (count == 0) {
		for (int i = x - 1; i <= x + 1; i++) {
			for (int j = y - 1; j <= y + 1; j++) {
				opened += OpenBoard(mine, show, r, c, i, j);
			}
		}
	}
	return opened;
}

// 排雷主循环：翻开写 "行 列"，插旗写 "f 行 列"
// 返回值：true = 排雷成功，false = 踩雷或中途退出
bool FindMine(Board& mine, Board& show, int r, int c, int mineCount) {
	int win = 0;              // 已翻开的格子数
	int steps = 0;            // 操作步数
	int flags = 0;            // 已插旗数量
	bool firstClick = true;   // 是否还没翻开过任何格子
	int total = r * c - mineCount;   // 需要翻开的安全格总数
	string line;

	while (win < total) {
		cout << "剩余雷数：" << mineCount - flags
			<< "    已走步数：" << steps << "\n";
		cout << "请输入（翻开：行 列    插旗：f 行 列）：\n";

		// 整行读入再解析，任何非法输入都不会让 cin 卡死
		if (!getline(cin >> ws, line)) {
			cout << "\n输入结束，退出本局。\n";
			return false;
		}
		istringstream iss(line);
		string cmd;
		iss >> cmd;
		if (cmd.empty()) continue;

		int x = 0, y = 0;
		bool isFlag = (cmd == "f" || cmd == "F");
		if (isFlag) {
			iss >> x >> y;
		}
		else {
			x = atoi(cmd.c_str());
			iss >> y;
		}

		if (x < 1 || x > r || y < 1 || y > c) {
			cout << "输入的坐标不合法，请重新输入！\n";
			continue;
		}

		// ---------- 插旗 ----------
		if (isFlag) {
			if (show[x][y] == 'F') {
				show[x][y] = '*';
				flags--;
				cout << "已取消 (" << x << "," << y << ") 的旗子。\n";
			}
			else if (show[x][y] != '*') {
				cout << "该位置已经翻开，不能再插旗！\n";
				continue;
			}
			else {
				show[x][y] = 'F';
				flags++;
				cout << "已在 (" << x << "," << y << ") 插旗。\n";
			}
			steps++;
			Displayboard(show, r, c);
			continue;
		}

		// ---------- 翻开 ----------
		if (show[x][y] == 'F') {
			cout << "该位置插了旗，请先取消旗子再翻开！\n";
			continue;
		}
		if (show[x][y] != '*') {
			cout << "该位置已排查过，请重新输入！\n";
			continue;
		}

		// 第一次真正翻开时才布雷，并给点击点留出安全区
		if (firstClick) {
			SetMine(mine, r, c, mineCount, x, y);
			firstClick = false;
		}

		if (mine[x][y] == '1') {
			cout << "很遗憾，你踩到雷了！\n";
			DisplayResult(mine, show, r, c);
			return false;
		}

		win += OpenBoard(mine, show, r, c, x, y);
		steps++;
		Displayboard(show, r, c);

		if (win == total) {
			cout << "恭喜你，排雷成功！共 " << steps << " 步\n";
			DisplayResult(mine, show, r, c);
			return true;
		}
	}
	return true;
}

//mine数组里的1表示有雷，0表示没有雷
//show数组里的*表示未翻开，F表示插旗，数字表示周围雷的数量
//(r+2)行(c+2)列均填入数据，但仅显示r行c列，边界行列用于计算周围雷的数量
//初始化-首次点击布雷-排查雷
