cmake_minimum_required(VERSION 3.21)

project(Assignment1)

add_executable(
	Assignment1 
	include/Triangle.hpp
	include/rasterizer.hpp

	source/Triangle.cpp
	source/rasterizer.cpp
	source/main.cpp
 "launch.vs.json")

# 告诉编译器：头文件在哪
target_include_directories(
    Assignment1
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 依赖 Eigen
find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(Assignment1 PRIVATE Eigen3::Eigen)

# OpenCV（vcpkg 提供的是 CONFIG 模式）
find_package(OpenCV CONFIG REQUIRED)
target_link_libraries(Assignment1 PRIVATE opencv_core opencv_imgproc opencv_highgui)
