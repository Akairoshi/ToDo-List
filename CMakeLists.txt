cmake_minimum_required(VERSION 3.15)
project(todolist)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(todolist
    src/main.cpp
)
target_include_directories(todolist PRIVATE ${CMAKE_SOURCE_DIR}/external/SelfCreatedFunc/include)