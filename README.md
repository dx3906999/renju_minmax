# Renju Minmax

这个项目是C语言课程的大作业，主要采用min-max算法和alpha-beta剪枝算法实现了一个多线程、带禁手的五子棋AI

## 项目结构

- `src`：源码目录
  - `renju.c`：五子棋基本功能实现
  - `referee.c`：五子棋禁手、棋型判断及裁判功能的实现
  - `state.c`：棋盘状态的封装实现
  - `evaluate.c`：五子棋棋局评分的实现
  - `minmax.c`：min-max算法及alpha-beta剪枝算法的实现
  - `thread_pool.c`：线程池的实现
  - `utils.c`：一些工具函数的实现
- `inc`：头文件目录
- `README.md`：项目说明文档
- `CMakeLists.txt`：CMake构建脚本

## 附加说明

- 在 `linux` 上终端字体可能不支持
- 在棋局过程中，当轮到自己落子时，输入`q` 可以退出，`r` 可以悔棋，`w` 保存棋局到 `history.txt`
