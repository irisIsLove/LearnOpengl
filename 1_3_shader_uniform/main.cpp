#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/std.h>

const std::uint32_t SCR_WIDTH = 800;
const std::uint32_t SCR_HEIGHT = 600;

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

  while (!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}
