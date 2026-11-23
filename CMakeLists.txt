
cmake_minimum_required(VERSION 3.16)
project(mva_robotics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Pybind11
find_package(pybind11 CONFIG REQUIRED)

# Python module
pybind11_add_module(mva_robotics bindings.cpp)

# Eigen headers
target_include_directories(mva_robotics PRIVATE /usr/local/include/eigen3)
