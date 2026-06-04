cmake_minimum_required(VERSION 3.25)

project(test_project CXX)

target_include_directories(${target_name} PRIVATE

)


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

