
#include "GL.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace GL {
	GLFWwindow* _window;

	bool Init(int width, int height, std::string title) 
	{
		// Initialize GLFW
		if (!glfwInit()) return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

		// Create a GLFW window
		_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

		if (_window == NULL) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		// Hide the mouse cursor
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glEnable(GL_DEPTH_TEST);
		
		return true;
	}

	void Post_Render()
	{
		SwapBuffersPollEvents();
	}

	void SwapBuffersPollEvents()
	{
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	GLFWwindow* GetWindowPointer()
	{
		return _window;
	}

	bool WindowIsOpen()
	{
		return !glfwWindowShouldClose(_window);
	}

	void SetWindowShouldClose(bool value)
	{
		glfwSetWindowShouldClose(_window, value);
	}

	void GetWindowSize(int* width, int* height) {
		glfwGetWindowSize(_window, width, height);
	}

	void Cleanup()
	{
		glfwTerminate();
	}

}