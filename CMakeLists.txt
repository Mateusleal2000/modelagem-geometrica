cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

project(imgEditor LANGUAGES CXX)


add_executable(decompModeling main.cpp Box.cpp Node.cpp OctTree.cpp TestSolid.cpp Sphere.cpp)


