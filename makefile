# Makefile for the project

# 编译器
CC = gcc

# 编译标志
CFLAGS = -Wall -g -Iinc

# 源文件目录和头文件目录
SRC_DIR = src
INC_DIR = inc
BLD_DIR = build

# 源文件和目标文件
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# 输出的可执行文件
TARGET = renju.exe

# 默认目标
all: $(TARGET)

# 生成可执行文件
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 

# 编译源文件
%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# 清理目标
clean:
	del $(OBJ) $(TARGET)

.PHONY: all clean

