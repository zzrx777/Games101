cmake_minimum_required(VERSION 3.21)
project(CGL)

# 设置包含目录供外部使用
set(CGL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE INTERNAL "")

# 进入源码目录
add_subdirectory(src)
