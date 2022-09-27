#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool processInput(GLFWwindow* window)														//function where all input processing happens, here for organizational purposes
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return true;
	}
	return false;
}
void framebuffer_size_callback(GLFWwindow* window, int x, int y)
{
	glViewport(0, 0, x, y);
}
GLFWwindow* windowInit (int windowX, int windowY, const char* windowName ) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(windowX, windowY, windowName, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);						//for resizing
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	glViewport(0, 0, windowX, windowY);
	return window;
}