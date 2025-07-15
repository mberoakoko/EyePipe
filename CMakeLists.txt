cmake_minimum_required(VERSION 3.22.1)
project(EyePipe)

set(CMAKE_CXX_STANDARD 23)

add_executable(EyePipe main.cpp
        include/eye_detail.hpp
        include/eye_functional.hpp
        include/mapping.hpp
        include/eye_pipe_pair.hpp
        include/eye_pipe_from.hpp
        include/eype_pipe_fork_into.hpp)
