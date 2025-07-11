cmake_minimum_required(VERSION 3.22.1)
project(EyePipe)

set(CMAKE_CXX_STANDARD 23)

add_executable(EyePipe main.cpp
        include/eye_detail.hpp)
