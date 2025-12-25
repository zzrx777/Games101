cmake_minimum_required(VERSION 3.21)

project(Assignment5)

add_executable(Assignment5
	include/global.hpp
	include/Light.hpp
	include/Object.hpp
	include/Renderer.hpp
	include/Scene.hpp
	include/Sphere.hpp
	include/Triangle.hpp
	include/Vector.hpp
	
	source/Renderer.cpp
	source/Scene.cpp
	source/main.cpp
)

target_include_directories(Assignment5 
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)