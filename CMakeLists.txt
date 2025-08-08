cmake_minimum_required(VERSION 3.16)

project(MyGameEngine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Sandbox)