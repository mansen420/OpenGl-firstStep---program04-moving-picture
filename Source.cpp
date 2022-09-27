#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SHADER_CLASS.h"
#include "BOILER_PLATE.h"
const int x = 1000;
const int y = 1000;
int main() {
	GLFWwindow* window{ windowInit(x, y, "opengl") };
	//
	float vertexData[]
	{
		//aPos			//tex			//aColor
		1.f,1.0f,0.0f,	1.0f,1.0f,		1.0,0.5f,0.0f,		//top right
		1.0,-1.0f,0.0f,	1.0f,0.0f,		0.0f,0.5f,1.0f,		//bottom right
		-1.0f,1.0f,0.0f, 0.0f,1.0f,		0.5, 1.0f, 0.0f,	//top left
		-1.0,-1.0f,0.0f, 0.0f,0.0f,		0.5, 0.0f, 1.0f		//bottom left
	};
	unsigned int indices[]{
		0,1,2,
		2,3,1
	};
	//
	unsigned int texture01,texture02;
	glGenTextures(1, &texture01);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texture01);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nchannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("C:/Users/msi/Desktop/texture03.jpg", &width, &height, &nchannels, 0);
	if (!data)
	{
		std::cout << "No data" << "\n" << stbi_failure_reason() << "\n";
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
		//2nd texture 
	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &texture02);
	glBindTexture(GL_TEXTURE_2D, texture02);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("C:/Users/msi/Desktop/sui.png", &width, &height, &nchannels, 0);
	if (!data)
	{
		std::cout << "No data" << "\n" << stbi_failure_reason() << "\n";
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	//
	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float)*3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float)*5));
	glEnableVertexAttribArray(2);
	//
	Shader shaders("vertexShader.glsl", "fragShader.glsl");
	//	uniforms
	shaders.use();
	glUniform1i((glad_glGetUniformLocation(shaders.ID, "texture01")), 0);
	shaders.setInt("texture02", 1);
	//
	//
	int mixer_status_ID = 0;
	float hori, verti, mixer;
	glGetUniformfv(shaders.ID, glGetUniformLocation(shaders.ID, "vertical"), &verti);
	glGetUniformfv(shaders.ID, glGetUniformLocation(shaders.ID, "horizontal"), &hori);
	glGetUniformfv(shaders.ID, glGetUniformLocation(shaders.ID, "mix_setting"), &mixer);
	float x = 0; float y = 0; float theta = 0;
	std::cout << "start" << "\n";

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
			//
		shaders.setFloat("mix_setting", mixer);
			//
		if (mixer_status_ID == 0) {
			mixer += 0.01;
			std::cout << "increase :D\n"<<mixer<<"\n";
			if (mixer >= 1) {
				std::cout << "CALL THE DECREASE DEPARTMENT\n";
				mixer_status_ID = 1;
			}
		}
		if (mixer_status_ID == 1) {
			mixer -= 0.1;
			std::cout << "decrease :D\n"<<mixer<<"\n";
			if (mixer <= 0) {
				mixer_status_ID = 0;
				std::cout << "CALL THE INCREASE DEPARTMENT\n";
			}
		}
			//
		glBindVertexArray(VAO);
		shaders.use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
			//
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << "end" << "\n";
	glfwTerminate();
	return 0;
}


/*
	DOCUMENTATION/DEBUGGING
GLAD/GLFW
	1.you must make sure to set current context before using any gl functions, otherwise GLAD won't be active
	2.GLFW window dimensions must match gl viewport dimensions 
Vertex Attribute Pointer
	1.the offset is specified in bytes!
*/