cmake_minimum_required(VERSION 3.21)

project(Assignment3)

add_executable(Assignment3
	include/global.hpp
	include/rasterizer.hpp
	include/Triangle.hpp
	include/Shader.hpp
	include/Texture.hpp
	include/OBJ_loader.h

	source/rasterizer.cpp
	source/Triangle.cpp
	source/Texture.cpp
	source/main.cpp
)

target_include_directories(Assignment3 
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(Assignment3 
	PRIVATE 
		ASSIGNMENT3_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

# Eigen
find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(Assignment3 PRIVATE Eigen3::Eigen)

# OpenCV
find_package(OpenCV CONFIG REQUIRED)
target_link_libraries(Assignment3 PRIVATE opencv_core opencv_imgproc opencv_highgui)