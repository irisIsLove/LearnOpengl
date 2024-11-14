add_executable(ShaderExercise3 main.cpp shader.cpp)
target_link_libraries(ShaderExercise3 PRIVATE LearnOpenGL)

add_custom_target(1_3_Exercise3
    DEPENDS ShaderExercise3
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/"
    "${CMAKE_CURRENT_BINARY_DIR}/shaders/"
)
