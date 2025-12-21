cmake_minimum_required(VERSION 3.21)

project(Assignment2)

add_executable(Assignment2
	include/global.hpp
	include/rasterizer.hpp
	include/Triangle.hpp

	source/rasterizer.cpp
	source/Triangle.cpp
	source/main.cpp
)

target_include_directories(Assignment2 
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 依赖 Eigen
find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(Assignment2 PRIVATE Eigen3::Eigen)

# OpenCV（vcpkg 提供的是 CONFIG 模式）
find_package(OpenCV CONFIG REQUIRED)
target_link_libraries(Assignment2 PRIVATE opencv_core opencv_imgproc opencv_highgui)