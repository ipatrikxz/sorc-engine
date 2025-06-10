#pragma once

#include <string>

struct GLFWwindow;

/*
*	GL
*
*	Handles GLFW initialization, window management, and cleanup.
*	It encapsulates creating a window, making it the current context,
*	and loading OpenGL functions with GLAD.
* 
*/
namespace GL
{

	bool Init(int width, int height, std::string title);

	// Post-rendering function to swap buffers and poll events
	void Post_Render();

	// Swaps buffers and polls for events
	void SwapBuffersPollEvents();

	// Sets the window to close
	void SetWindowShouldClose(bool value);

	// Retrieves the current size of the window
	void GetWindowSize(int* width, int* height);

	// Returns a pointer to the GLFW window
	GLFWwindow* GetWindowPointer();

	// Checks if the window is still open
	bool WindowIsOpen();

	void Cleanup();
}