cmake_minimum_required(VERSION 3.15.0)
project(LearnOpenGL)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_library(LearnOpenGL INTERFACE)
target_compile_features(LearnOpenGL INTERFACE cxx_std_17)
target_link_libraries(LearnOpenGL INTERFACE glfw glad::glad fmt::fmt)

add_subdirectory(1_get_started)
