cmake_minimum_required(VERSION 3.21)

project(Assignment6)

add_executable(Assignment6 
    include/Renderer.hpp
    include/Object.hpp  
    include/Vector.hpp 
    include/Sphere.hpp 
    include/global.hpp 
    include/Triangle.hpp 
    include/Scene.hpp 
    include/Light.hpp 
    include/AreaLight.hpp   
    include/BVH.hpp 
    include/Bounds3.hpp 
    include/Ray.hpp 
    include/Material.hpp 
    include/Intersection.hpp
    include/OBJ_Loader.hpp

    source/Renderer.cpp 
    source/Vector.cpp
    source/main.cpp
    source/Scene.cpp
    source/BVH.cpp
)

target_include_directories(Assignment6 
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(Assignment6 
	PRIVATE 
		ASSIGNMENT6_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)