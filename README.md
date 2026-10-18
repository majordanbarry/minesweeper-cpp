# Minesweeper-CPP

> 用 C++ 写的经典扫雷游戏（控制台版）

[![C++](https://img.shields.io/badge/C%2B%2B-blue.svg)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE.txt)
[![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)](#)
[![Status](https://img.shields.io/badge/status-in%20development-yellow.svg)](#)

<!-- 演示 GIF：录好后放到 screenshots/demo.gif，然后删掉下面两行的注释符号
![游戏演示](screenshots/demo.gif)
-->

9×9 棋盘、10 颗雷的经典扫雷。采用双数组设计 + 边界填充，代码拆分为声明、逻辑、入口三个模块。

## 如何运行

需要 Visual Studio 2022（安装时勾选"使用 C++ 的桌面开发"工作负载）。

```bash
git clone https://github.com/majordanbarry/minesweeper-cpp.git
```

双击打开 `game.slnx`，按 `F5` 运行。

## 玩法

1. 运行后输入 `1` 开始游戏
2. 输入 `行 列`（取值 1~9）翻开格子
3. 数字表示该格周围 8 格中的雷数，踩到雷即失败
4. 翻开全部 71 个安全格即为胜利

## 功能

- [x] 9×9 棋盘，10 颗雷
- [x] 随机布雷（不重复落点）
- [x] 自动计算周围雷数
- [x] 完整的胜负判定与菜单循环
- [ ] 空白区域递归展开
- [ ] 插旗标记
- [ ] 首次点击不踩雷
- [ ] 多难度选择
- [ ] 计时器
- [ ] 重构为面向对象

## 项目结构

```
game/
├── game.slnx             # Visual Studio 解决方案
├── game/
│   ├── main.cpp          # 程序入口：菜单与主循环
│   ├── game.h            # 宏定义与函数声明
│   └── game.cpp          # 核心逻辑：初始化、显示、布雷、排雷
├── README.md
└── LICENSE.txt
```

## 技术实现

- **双数组设计**：`mine` 数组存雷（`'1'` 有雷 / `'0'` 无雷），`show` 数组存显示状态（`'*'` 未翻开 / 数字表示周围雷数），数据结构与展示职责分离
- **边界填充技巧**：实际开辟 11×11 的数组，只显示中间的 9×9，统计周围 8 格雷数时无需额外判断数组越界
- **模块化拆分**：声明与定义分离（`game.h` / `game.cpp`），程序入口单独置于 `main.cpp`

## 许可

[MIT](LICENSE.txt)
