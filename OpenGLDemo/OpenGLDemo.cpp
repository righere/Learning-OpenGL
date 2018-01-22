#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderUtils.h"

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//const char *vertexShaderSource = "#version 330 core \n								  \
//								  layout (location = 0) in vec3 aPos; \n			  \
//								  layout (location = 1) in vec3 color;                \
//								  out vec3 vertexColor;								  \
//								  void main() \n									  \
//								  {													  \
//								  	gl_Position = vec4(aPos, 1.0); \n                 \
//								    vertexColor = color;							  \
//								  }\0";
//
//const char *fragmentShaderSource = "#version 330 core \n							  \
//									out vec4 FragColor; \n							  \
//									in vec3 vertexColor;							  \
//																					  \
//									void main() \n									  \
//									{ \n											  \
//										FragColor = vec4(vertexColor, 1.0f);	          \
//									}\n\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __apple__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "OpenGL Learning", glfwGetPrimaryMonitor(), NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//回调，调整窗口
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader("OpenGLDemo.vs", "OpenGLDemo.fs");

	float vertices[] = {
		0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//setup vertex data and configure vertex attributes
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	//bind VBO data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//clear color and buffer
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw triangle
		//set variable color value
		float xoff = 0.5f;

		glUniform1f(glGetUniformLocation(shader.ID, "xoff"), xoff);

		shader.use();
		glBindVertexArray(VAO);


		glDrawArrays(GL_TRIANGLES, 0, 3);

		//swapbuffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
