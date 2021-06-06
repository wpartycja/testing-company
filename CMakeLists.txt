cmake_minimum_required(VERSION 3.17)
project(proj)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(proj employee.cpp publisher.cpp game.cpp main.cpp simulation.cpp)
