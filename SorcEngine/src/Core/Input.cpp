#include "Input.h"
#include "GL.h"

bool _keyPressed[372];
bool _keyDown[372];
bool _keyDownLastFrame[372];

void Input::Update()
{
	GLFWwindow* window = GL::GetWindowPointer();
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
