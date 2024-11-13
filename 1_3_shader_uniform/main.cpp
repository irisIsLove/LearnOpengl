#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/std.h>

const std::uint32_t SCR_WIDTH = 800;
const std::uint32_t SCR_HEIGHT = 600;

const char* vertex_shader_source = "#version 330 core\n"
                                   "layout (location = 0) in vec3 a_pos;\n"
                                   "void main()\n"
                                   "{\n"
                                   "  gl_Position = vec4(a_pos, 1.0);\n"
                                   "}\0";

const char* fragment_shader_source = "#version 330 core\n"
                                     "out vec4 frag_color;\n"
                                     "uniform vec4 vertex_color;\n"
                                     "void main()\n"
                                     "{\n"
                                     "  frag_color = vertex_color;\n"
                                     "}\0";

void
on_set_framebuffer_size(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void
process_input(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int
main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window =
    glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shader Uniform", nullptr, nullptr);
  if (!window) {
    fmt::print("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, on_set_framebuffer_size);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fmt::print("Failed to initialize GLAD\n");
    return -1;
  }

  // 着色器编译信息
  int success;
  char info_log[512];

  // 编译顶点着色器
  std::uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
    fmt::print("Vertex shader compilation failed: {}\n", info_log);
  }

  // 编译片段着色器
  std::uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
  glCompileShader(fragment_shader);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
    fmt::print("Fragment shader compilation failed: {}\n", info_log);
  }

  // 链接着色器程序
  std::uint32_t shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  glGetShaderiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
    fmt::print("Shader program linking failed: {}\n", info_log);
  }
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  float vertices[] = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f,  -0.5f, 0.0f, // right
    0.0f,  0.5f,  0.0f, // top
  };

  // 创建顶点缓冲对象
  std::uint32_t VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // 创建顶点数组对象
  std::uint32_t VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // update shader uniform
    float time_value = glfwGetTime();
    float green_value = std::sin(time_value) / 2.0f + 0.5f;
    int vertex_color_location =
      glGetUniformLocation(shader_program, "vertex_color");
    glUseProgram(shader_program);
    glUniform4f(vertex_color_location, 0.0f, green_value, 0.0f, 1.0f);

    // render graphic
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glDeleteProgram(shader_program);

  glfwTerminate();
}
