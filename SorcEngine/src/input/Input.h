#pragma once
#include "Common.h"

enum EDirection {
	FORWARD = 1,
	BACKWARD = 2,
	LEFT = 3,
	RIGHT = 4,
	UP = 5,
	DOWN = 6
};

enum class EInputButton
{
	Left = 0,
	Right = 1,
	Middle = 2,
	None = 9
};

struct s_CursorPos
{
	double mouseX = 0;
	double mouseY = 0;
	double lastMouseX = 0;
	double lastMouseY = 0;
	double mouseOffsetX = 0;
	double mouseOffsetY = 0;
};

namespace Input 
{

	void Update(GLFWwindow* window);
	bool KeyPressed(unsigned int keycode);
	bool KeyDown(unsigned int keycode);

	s_CursorPos UpdateCursorPos(s_CursorPos lastCursorPos, double inMouseX, double inMouseY);


	
}