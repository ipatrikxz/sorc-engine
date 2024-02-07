#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <string>

/*
*	GL
*
*	Handles GLFW initialization, window management, and cleanup.
*	It encapsulates creating a window, making it the current context,
*	and loading OpenGL functions with GLAD.
*/
namespace GL {

	void Init(int width, int height, std::string title);
	GLFWwindow* GetWindowPointer();
	bool WindowIsOpen();
	void SetWindowShouldClose(bool value);
	void SwapBuffersPollEvents();
	void Cleanup();

}