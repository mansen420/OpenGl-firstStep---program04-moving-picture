#ifndef BOIL_ME_HARDER
#define BOIL_ME_HARDER
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SHADER_CLASS.h"

bool processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int x, int y);
GLFWwindow* windowInit(int windowX, int windowY, const char* windowName);
#endif // !BOIL_ME_HARDER

