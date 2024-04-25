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
        board.cpp
        Moth.h
        Moth.cpp)
# Adjust the path according to where SFML is installed
set(SFML_DIR /usr/local/Cellar/sfml/2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

# The include path might also need to be adjusted
include_directories(/usr/local/Cellar/sfml/2.6.1/include)
target_link_libraries(CA2_Cpp_Bug sfml-system sfml-window sfml-graphics sfml-audio)