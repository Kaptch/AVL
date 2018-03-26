cmake_minimum_required(VERSION 3.9)
project(tree1)

set(CMAKE_CXX_STANDARD 17)

add_executable(tree1 main.cpp AVL.h pairComp.h priority_queue.h stringData.h csv.h)