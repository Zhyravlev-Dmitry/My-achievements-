cmake_minimum_required(VERSION 3.17.3)
project(dequeTests)

set(CMAKE_CXX_STANDARD 20)

add_executable(dequeTests main.cpp DequeTests.cpp DequeTests.h TestLib.h deque.h deque_ok.h my_test.cpp)
add_executable(Mesh_test test.cpp)
add_executable(my_test my_test.cpp)