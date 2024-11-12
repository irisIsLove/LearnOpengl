cmake_minimum_required(VERSION 3.15.0)
project(HelloWindow)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(HelloWindow main.cpp)
target_link_libraries(HelloWindow PRIVATE glfw glad::glad)
