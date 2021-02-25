cmake_minimum_required(VERSION 3.12)


set(CMAKE_CXX_STANDARD 17)

project(bm	)

add_library(bm STATIC
        sys/hooks.cpp
        sys/startup.cpp)

target_include_directories(bm PUBLIC
        ../tl/tl/include)

