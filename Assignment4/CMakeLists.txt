cmake_minimum_required(VERSION 3.21)

project(Assignment4)

add_executable(Assignment4
	source/main.cpp
)

target_include_directories(Assignment4 
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

# OpenCV
find_package(OpenCV CONFIG REQUIRED)
target_link_libraries(Assignment4 PRIVATE opencv_core opencv_imgproc opencv_highgui)