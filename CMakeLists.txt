# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject)
set(CMAKE_CXX_STANDARD 20)

# Add an executable target (your source files go here)
add_executable(main example/main.cpp)

