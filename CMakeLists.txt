cmake_minimum_required(VERSION 3.21)

# 告诉 vcpkg 在配置阶段自动安装 vcpkg.json 里的依赖
set(VCPKG_MANIFEST_INSTALL ON CACHE BOOL "")

if(NOT DEFINED ENV{VCPKG_ROOT})
    message(FATAL_ERROR "环境变量 VCPKG_ROOT 未设置，请先下载 vcpkg 并设置 VCPKG_ROOT")
endif()

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# 项目信息
project(Games101)

# C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加各 Assignment
add_subdirectory(Assignment0)
add_subdirectory(Assignment1)
add_subdirectory(Assignment2)
add_subdirectory(Assignment3)
add_subdirectory(Assignment4)
add_subdirectory(Assignment5)
add_subdirectory(Assignment6)