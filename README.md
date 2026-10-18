# Minesweeper-CPP

> 用 C++ 写的经典扫雷游戏（控制台版）

[![C++](https://img.shields.io/badge/C%2B%2B-blue.svg)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE.txt)
[![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)](#)
[![Status](https://img.shields.io/badge/status-v1.0-brightgreen.svg)](#)

<!-- 演示 GIF：录好后放到 screenshots/demo.gif，然后删掉下面两行的注释符号
![游戏演示](screenshots/demo.gif)
-->

初级 9×9 / 中级 16×16 / 高级 16×30 三档难度的经典扫雷。采用双数组设计 + 边界填充，棋盘尺寸在运行时确定，代码拆分为声明、逻辑、入口三个模块。

## 如何运行

需要 Visual Studio 2022（安装时勾选"使用 C++ 的桌面开发"工作负载）。

```bash
git clone https://github.com/majordanbarry/minesweeper-cpp.git
```

双击打开 `game.slnx`，按 `F5` 运行。

## 玩法

1. 运行后先选难度：`1` 初级 / `2` 中级 / `3` 高级，`0` 退出
2. 输入 `行 列` 翻开格子
3. 输入 `f 行 列` 插旗标记，再输入一次取消
4. 数字表示该格周围 8 格中的雷数，踩到雷即失败
5. 翻开全部安全格即为胜利（初级 71 格 / 中级 216 格 / 高级 381 格）
6. 结束后回答 `y` 再来一局，其他任意键返回菜单

> 第一次点击保证不会踩雷，必定翻开一片空白区，方便开局。

## 功能

- [x] 三档难度：初级 9×9/10 雷、中级 16×16/40 雷、高级 16×30/99 雷
- [x] 随机布雷（不重复落点）
- [x] 自动计算周围雷数
- [x] 空白区域递归展开（DFS 洪水填充）
- [x] 插旗标记（`f 行 列` 切换）
- [x] 首次点击不踩雷（自动留出 3×3 安全区）
- [x] 剩余雷数、已走步数、用时实时显示
- [x] 对局计时器
- [x] 结束后可再来一局
- [x] 完整的胜负判定与菜单循环
- [x] 游戏结束揭晓整片雷区
- [x] 非法输入保护（输错不会死循环）
- [ ] 重构为面向对象

## 项目结构

```
game/
├── game.slnx             # Visual Studio 解决方案
├── game/
│   ├── main.cpp          # 程序入口：难度菜单、开局与再来一局
│   ├── game.h            # GameConfig 结构体与函数声明
│   └── game.cpp          # 核心逻辑：初始化、显示、布雷、排雷
├── README.md
└── LICENSE.txt
```

## 技术实现

- **动态尺寸**：棋盘用 `vector<vector<char>>` 在运行时分配，同一套逻辑支持任意行列数；一档难度只是一组配置参数（`GameConfig` 的 `name` / `rows` / `cols` / `mines`）
- **双数组设计**：`mine` 数组存雷（`'1'` 有雷 / `'0'` 无雷），`show` 数组存显示状态（`'*'` 未翻开 / `'F'` 插旗 / 数字表示周围雷数），数据结构与展示职责分离
- **空白区递归展开**：点击到周围无雷的格子时，用深度优先搜索（DFS）向 8 个方向递归展开，遇到数字格自动停止；函数返回本次揭开的总格数用于胜利判定
- **边界填充技巧**：实际开辟 `(r+2) × (c+2)` 的数组，只显示中间的 `r × c`，统计周围 8 格雷数时无需额外判断数组越界
- **输入容错**：整行读入后交给 `istringstream` 解析，配合 `getline` 的返回值判断流状态，任何非法输入都不会让 `cin` 进入失败态死循环
- **模块化拆分**：声明与定义分离（`game.h` / `game.cpp`），程序入口单独置于 `main.cpp`

## 许可

[MIT](LICENSE.txt)
