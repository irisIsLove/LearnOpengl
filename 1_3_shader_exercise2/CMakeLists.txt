add_executable(ShaderExercise2 main.cpp shader.cpp)
target_link_libraries(ShaderExercise2 PRIVATE LearnOpenGL)

add_custom_target(1_3_Exercise2
    DEPENDS ShaderExercise2
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/"
    "${CMAKE_CURRENT_BINARY_DIR}/shaders/"
)
