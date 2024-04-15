cmake_minimum_required(VERSION 3.27)
project(CA2_Cpp_Bug)

set(CMAKE_CXX_STANDARD 17)

add_executable(CA2_Cpp_Bug main.cpp
        Bug.h
        Bug.cpp
        Crawler.h
        Crawler.cpp
        Hopper.h
        Hopper.cpp
        board.h
        board.cpp)
