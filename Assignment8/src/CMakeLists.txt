cmake_minimum_required(VERSION 3.21)

# 设置源码
set(APPLICATION_SOURCE
    rope.cpp
    application.cpp
    main.cpp
)

# 添加执行程序
add_executable(Assignment8 ${APPLICATION_SOURCE})

# 包含目录：自己的 src + CGL 的头文件
target_include_directories(Assignment8 PRIVATE . ${CGL_INCLUDE_DIRS})

# 链接 CGL 库和其他依赖
target_link_libraries(Assignment8
    PRIVATE
    CGL
    GLEW::GLEW
    glfw
    OpenGL::GL
    Freetype::Freetype
    Threads::Threads
    $<IF:$<TARGET_EXISTS:getopt::getopt_shared>,getopt::getopt_shared,getopt::getopt_static>
)

# Windows 下拷贝 dll 的辅助处理（可选）
if(WIN32)
    set_target_properties(Assignment8 PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Assignment8")
endif()
