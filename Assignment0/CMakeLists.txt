cmake_minimum_required(VERSION 3.21)

project(Assignment0)

add_executable(Assignment0 source/main.cpp)

# 依赖 Eigen
find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(Assignment0 PRIVATE Eigen3::Eigen)