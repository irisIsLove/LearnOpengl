#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/std.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertext_shader_source =
  "#version 330 core\n"
  "layout (location = 0) in vec3 a_pos;\n"
  "void main()\n"
  "{\n"
  "\tgl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);\n"
  "}\0";

const char* fragment_shader_source =
  "#version 330 core\n"
  "out vec4 frag_color;\n"
  "void main()\n"
  "{\n"
  "\tfrag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0";

void
framebuffer_size_callback(GLFWwindow* window, int width, int height)
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

  GLFWwindow* window =
    glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloTriangle", nullptr, nullptr);
  if (window == nullptr) {
    fmt::println("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fmt::println("Failed to initialize GLAD");
    return -1;
  }

  std::uint32_t vertext_shader;
  vertext_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertext_shader, 1, &vertext_shader_source, nullptr);
  glCompileShader(vertext_shader);

  int success;
  char info_log[512];
  glGetShaderiv(vertext_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertext_shader, 512, nullptr, info_log);
    fmt::println("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}", info_log);
  }

  std::uint32_t fragment_shader;
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
    fmt::println("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}", info_log);
  }

  std::uint32_t shader_program;
  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertext_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  glGetShaderiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader_program, 512, nullptr, info_log);
    fmt::println("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}", info_log);
  }
  glDeleteShader(vertext_shader);
  glDeleteShader(fragment_shader);

  float vertices[] = {
    0.5f,  0.5f,  0.0f, // top right
    0.5f,  -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f  // top left
  };
  unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first Triangle
    1, 2, 3  // second Triangle
  };

  std::uint32_t VBO;
  glGenBuffers(1, &VBO);

  std::uint32_t EBO;
  glGenBuffers(1, &EBO);

  std::uint32_t VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteProgram(shader_program);
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();
}