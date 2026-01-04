cmake_minimum_required(VERSION 3.21)
project(Assignment8)

add_compile_definitions(_USE_MATH_DEFINES) #M_PI

# 查找 vcpkg 安装的包
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(Threads REQUIRED)
find_package(getopt CONFIG REQUIRED)

# 进入 CGL 核心库
add_subdirectory(CGL)

# 进入作业源代码
add_subdirectory(src)