#include "shader.h"

#include <fmt/std.h>

#include <fstream>
#include <sstream>

Shader::Shader(std::string_view vertex_path, std::string_view fragment_path)
{
  std::string vertex_code, fragment_code;
  std::ifstream vert_file, frag_file;
  vert_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  frag_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    std::stringstream vert_stream, frag_stream;

    vert_file.open(vertex_path);
    vert_stream << vert_file.rdbuf();
    vertex_code = vert_stream.str();
    vert_file.close();

    frag_file.open(fragment_path);
    frag_stream << frag_file.rdbuf();
    fragment_code = frag_stream.str();
    frag_file.close();

  } catch (std::ifstream::failure& e) {
    fmt::println(
      stderr, "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: {}", e.what());
  }
  int success;
  char info_log[512];
  const char* vert_source = vertex_code.c_str();
  const char* frag_source = fragment_code.c_str();

  std::uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vert_source, nullptr);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  check_compile_errors(vertex_shader, "VERTEX");

  std::uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &frag_source, nullptr);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  check_compile_errors(fragment_shader, "FRAGMENT");

  ID = glCreateProgram();
  glAttachShader(ID, vertex_shader);
  glAttachShader(ID, fragment_shader);
  glLinkProgram(ID);
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  check_compile_errors(ID, "PROGRAM");

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
  glDeleteProgram(ID);
}

void
Shader::use() const
{
  glUseProgram(ID);
}

void
Shader::set_bool(std::string_view name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID, name.data()), static_cast<int>(value));
}

void
Shader::set_int(const std::string_view name, int value) const
{
  glUniform1i(glGetUniformLocation(ID, name.data()), value);
}

void
Shader::set_float(const std::string_view name, float value) const
{
  glUniform1f(glGetUniformLocation(ID, name.data()), value);
}

void
Shader::set_vec3(const std::string_view name, float x, float y, float z) const
{
  glUniform3f(glGetUniformLocation(ID, name.data()), x, y, z);
}

void
Shader::check_compile_errors(std::uint32_t shader, std::string_view type) const
{
  int success;
  char info_log[512];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 512, nullptr, info_log);
      fmt::println(stderr,
                   "ERROR::SHADER_COMPILATION_ERROR of type: {}\n{}",
                   type,
                   info_log);
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 512, nullptr, info_log);
      fmt::println(
        stderr, "ERROR::PROGRAM_LINKING_ERROR of type: {}\n{}", type, info_log);
    }
  }
}
