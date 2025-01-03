#include "shader.h"

#include <GLFW/glfw3.h>
#include <fmt/std.h>

constexpr std::uint32_t WIDTH = 800;
constexpr std::uint32_t HEIGHT = 600;

void
process_input(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void
on_set_framebuffer_size(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void
get_rgb(int& r, int& g, int& b)
{
  if (r == 255 && g < 255 && b == 0)
    ++g;
  else if (r > 0 && g == 255 && b == 0)
    --r;
  else if (r == 0 && g == 255 && b < 255)
    ++b;
  else if (r == 0 && g > 0 && b == 255)
    --g;
  else if (r < 255 && g == 0 && b == 255)
    ++r;
  else if (r == 255 && g == 0 && b > 0)
    --b;
}

int
main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window =
    glfwCreateWindow(WIDTH, HEIGHT, "Shader Uniform", nullptr, nullptr);
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

  float vertices[] = {
    // positions                     // reference
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
    0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, // top
  };

  Shader shader("shaders/shader.vert", "shaders/shader.frag");

  std::uint32_t VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  std::uint32_t VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  // position attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attributes
  glVertexAttribPointer(
    1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  int r = 255, g = 0, b = 0;
  while (!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    get_rgb(r, g, b);
    float red = r / 255.0f;
    float green = g / 255.0f;
    float blue = b / 255.0f;
    shader.use();
    shader.set_vec3("vertex_color", red, green, blue);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}