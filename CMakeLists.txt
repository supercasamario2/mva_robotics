cmake_minimum_required(VERSION 3.28)
project(mva_robotics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

# Dependencies
find_package(Eigen3 CONFIG REQUIRED)
find_package(drake CONFIG REQUIRED)
find_package(pinocchio CONFIG REQUIRED)


# Python module
pybind11_add_module(mva_robotics
    src/bindings.cpp
)

add_executable(mva_test
    test/test.cpp
)

target_include_directories(mva_robotics PUBLIC include)

target_link_libraries(mva_robotics PUBLIC
    Eigen3::Eigen
    drake::drake
    pinocchio::pinocchio
)

target_include_directories(mva_test PRIVATE include)

target_link_libraries(mva_test PRIVATE
    Eigen3::Eigen
    drake::drake
    pinocchio::pinocchio
)