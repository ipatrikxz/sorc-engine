#include "Input.h"

#include <GLFW/glfw3.h>

namespace Input 
{

	bool _keyPressed[372];
	bool _keyDown[372];
	bool _keyDownLastFrame[372];

	void Input::Update(GLFWwindow* window)
	{
		for (int i = 30; i < 350; i++) {
			_keyDown[i] = (glfwGetKey(window, i) == GLFW_PRESS);
			_keyPressed[i] = (_keyDown[i] && !_keyDownLastFrame[i]);
			_keyDownLastFrame[i] = _keyDown[i];
		}
	}

	bool Input::KeyPressed(unsigned int keycode)
	{
		return _keyPressed[keycode];
	}

	bool Input::KeyDown(unsigned int keycode)
	{
		return _keyDown[keycode];
	}

	s_CursorPos UpdateCursorPos(s_CursorPos lastCursorPos, double inMouseX, double inMouseY)
	{
		s_CursorPos cursorPos = lastCursorPos;
		cursorPos.mouseX = inMouseX;
		cursorPos.mouseY = inMouseY;

		// Calculate offsets only if not the first frame
		if (cursorPos.lastMouseX != 0 || cursorPos.lastMouseY != 0) {
			cursorPos.mouseOffsetX = inMouseX - cursorPos.lastMouseX;
			cursorPos.mouseOffsetY = cursorPos.lastMouseY - inMouseY; // Invert Y for typical camera controls
		}
		else {
			cursorPos.mouseOffsetX = 0;
			cursorPos.mouseOffsetY = 0;
		}

		cursorPos.lastMouseX = inMouseX;
		cursorPos.lastMouseY = inMouseY;

		return cursorPos;
	}


	
}