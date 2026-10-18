#pragma once
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
#include<limits>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

// 棋盘用二维 vector 表示，尺寸在运行时才确定，因此同一份代码能支持任意难度
using Board = vector<vector<char>>;

// 一档难度的全部参数
struct GameConfig {
	const char* name;   // 难度名
	int rows;           // 显示出来的行数（不含边界）
	int cols;           // 显示出来的列数（不含边界）
	int mines;          // 雷数
};

// 每个格子占三个字符宽度，保证 1~30 的两位数列号不会挤在一起
const int CELL_W = 3;

// 初始化：把 board 调整为 totalR x totalC，并整体填成 set
void InitBoard(Board& board, int totalR, int totalC, char set);
void Displayboard(const Board& board, int r, int c);
void DisplayResult(const Board& mine, const Board& show, int r, int c);

// 布雷：避开首次点击点周围的 3x3 区域，保证第一下不会踩雷
void SetMine(Board& mine, int r, int c, int mineCount, int safeX, int safeY);

int GetMineCount(const Board& mine, int r, int c);

// 空白区递归展开，返回本次揭开的格数
int OpenBoard(const Board& mine, Board& show, int r, int c, int x, int y);

// 排雷主循环，返回 true 表示排雷成功
bool FindMine(Board& mine, Board& show, int r, int c, int mineCount);
