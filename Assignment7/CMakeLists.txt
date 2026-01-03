cmake_minimum_required(VERSION 3.21)

project(Assignment7)

add_executable(Assignment7 
    include/AreaLight.hpp
    include/Bounds3.hpp
    include/BVH.hpp
    include/global.hpp
    include/Intersection.hpp
    include/Light.hpp
    include/Material.hpp
    include/Object.hpp
    include/OBJ_Loader.hpp
    include/Ray.hpp
    include/Renderer.hpp
    include/Scene.hpp
    include/Sphere.hpp
    include/Triangle.hpp  
    include/Vector.hpp
    include/TaskQueue.hpp
    
    source/BVH.cpp
    source/main.cpp
    source/Renderer.cpp 
    source/Scene.cpp
    source/Vector.cpp     
 )

target_include_directories(Assignment7 
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(Assignment7 
	PRIVATE 
		ASSIGNMENT7_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)