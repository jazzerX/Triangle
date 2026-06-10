cmake_minimum_required(VERSION 3.29.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(target_name Triangle)

project(${target_name} CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

message(STATUS "Runtime directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Library directory: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "Archive directory: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

add_subdirectory(src)
