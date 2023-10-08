#include "Window.h"

#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>

int Window::width{0};
int Window::height{0};
GLFWwindow* Window::window{nullptr};
bool Window::error{false};

void Window::init(int width, int height, int versionMajor, int versionMinor,const std::string& windowName)
{
	Window::width = width;
	Window::height = height;
	glfwInit();		//Initialize GLFW for window stuff

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);	//Set the context versions to opengl 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, windowName.c_str(), 0, 0);	//Create the window

	error = window == NULL;	//error handling if window is not created
	if (error)
	{
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return;
	}


	glfwMakeContextCurrent(window);	//make the context current and error handling if initializing GLAD fails
	error = !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (error)
	{
		std::cout << "Failed to initialize GLAD\n";
		glfwTerminate();
		return;
	}

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int windowWidth, int windowHeight)->void	//Set up callback for when the window is resized
		{
			glViewport(0, 0, windowWidth, windowHeight);
			Window::setWidth(windowWidth);
			Window::setHeight(windowHeight);
			std::cout << "New window size (X: " << windowWidth << " ,Y: " << windowHeight << ")\n";
		});

	//Common settings for 2D games (transparency, depth testing)

	glEnable(GL_BLEND);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_DEPTH_TEST);
}