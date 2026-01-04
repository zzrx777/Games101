cmake_minimum_required(VERSION 3.21)

# 包含当前目录和 include 目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ../include)

set(CGL_SOURCE
    vector2D.cpp vector3D.cpp vector4D.cpp
    matrix3x3.cpp matrix4x4.cpp quaternion.cpp
    complex.cpp color.cpp osdtext.cpp osdfont.c
    viewer.cpp base64.cpp tinyxml2.cpp
)

add_library(CGL STATIC ${CGL_SOURCE})

# 链接 vcpkg 提供的库
target_link_libraries(CGL
    PUBLIC
    GLEW::GLEW
    glfw
    OpenGL::GL
    Freetype::Freetype
)

