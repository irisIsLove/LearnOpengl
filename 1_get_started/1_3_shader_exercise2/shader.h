#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string_view>

class Shader
{
public:
  std::uint32_t ID;

public:
  Shader(std::string_view vertex_path, std::string_view fragment_path);
  ~Shader();

  void use() const;
  void set_bool(const std::string_view name, bool value) const;
  void set_int(const std::string_view name, int value) const;
  void set_float(const std::string_view name, float value) const;
  void set_vec3(const std::string_view name, float x, float y, float z) const;

private:
  void check_compile_errors(std::uint32_t shader, std::string_view type) const;
};

#endif // SHADER_H
