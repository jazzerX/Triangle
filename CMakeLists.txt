cmake_minimum_required(VERSION 3.25)

set(target_name Triangle)
project(${target_name} CXX)

add_executable(${target_name})

add_subdirectory(src)
