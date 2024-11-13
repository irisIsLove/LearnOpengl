cmake_minimum_required(VERSION 3.5.0)
project(HelloTriangleExercise2)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(HelloTriangleExercise2 main.cpp)
target_link_libraries(HelloTriangleExercise2 PRIVATE glfw glad::glad fmt::fmt)
