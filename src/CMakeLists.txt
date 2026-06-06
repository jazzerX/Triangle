cmake_minimum_required(VERSION 3.29.5)

add_executable(${target_name})

target_sources(${target_name}
    PRIVATE
        main.cpp
)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(${target_name} PRIVATE
    glfw
    OpenGL::GL
    GLEW::GLEW
)
