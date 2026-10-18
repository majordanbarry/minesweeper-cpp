#pragma once
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<limits>
using namespace std;
#define easy_count 10
#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2
void Displayboard(char board[ROWS][COLS], int row, int col);
void InitBoard(char board[ROWS][COLS], int r, int c, char set);
void SetMine(char mine[ROWS][COLS], int r, int c);
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c);
int GetMineCount(char mine[ROWS][COLS], int r, int c);
int OpenBoard(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c);