add_executable(ShaderClass main.cpp shader.cpp)
target_link_libraries(ShaderClass PRIVATE LearnOpenGL)

add_custom_target(1_3ShaderCopy
    DEPENDS ShaderClass
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/"
    "${CMAKE_CURRENT_BINARY_DIR}/shaders/"
)
