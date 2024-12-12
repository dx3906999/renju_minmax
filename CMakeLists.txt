cmake_minimum_required(VERSION 3.10)

# Project name
project(Renju)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Source and header directories
set(SRC_DIR src)
set(INC_DIR inc)

# Collect all source files
file(GLOB SRC_FILES "${SRC_DIR}/*.c")

# Include directories
include_directories(${INC_DIR})

# Add the executable target
add_executable(renju ${SRC_FILES})

# Compiler flags
target_compile_options(renju PRIVATE -Wall -O2 -finput-charset=GBK -fexec-charset=GBK)
