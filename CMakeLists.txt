cmake_minimum_required(VERSION 3.16)

project(DomoticsBase)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_library(DomoticsBase
        src/mqtt/parsing_functions.cpp)

target_include_directories(DomoticsBase PUBLIC
        include)

add_subdirectory(tests)