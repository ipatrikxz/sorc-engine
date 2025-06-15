#pragma once

#include "InputManager.h"

#include <GLFW/glfw3.h>
#include "window/Window.h"

namespace input 
{

    void InputManager::processInput(window::RenderWindow& window)
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(window.getNativeWindow());

        glm::vec3 inputVector(0.0f);

        // Accumulate input directions (not world directions)
        if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS) inputVector.z += 1.0f;  // forward
        if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS) inputVector.z -= 1.0f;  // backward
        if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS) inputVector.x += 1.0f;  // right
        if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS) inputVector.x -= 1.0f;  // left
        if (glfwGetKey(glfwWindow, GLFW_KEY_E) == GLFW_PRESS) inputVector.y += 1.0f;  // up
        if (glfwGetKey(glfwWindow, GLFW_KEY_Q) == GLFW_PRESS) inputVector.y -= 1.0f;  // down

        // Pass raw input vector to camera - camera handles the rest
        if (glm::length(inputVector) > 0.0f)
        {
            movementDelegate(deltaTime, inputVector);
        }

		// close window on ESC key press
        if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        {
            window.setShouldClose();
        }

		// on right mouse press, capture mouse position            
        if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
			// Capture mouse position
            glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            double mouseX, mouseY;
            glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);
			handleMouseMovement(mouseX, mouseY);
        }
        
		// on mouse release, reset cursor
        if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
            glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            lastMouseX = 0;
            lastMouseY = 0;
        }
    }

    void InputManager::handleMouseMovement(double xpos, double ypos)
    {
        // First movement
        if (lastMouseX == 0 && lastMouseY == 0) 
        { 
            lastMouseX = xpos;
            lastMouseY = ypos;
            return;
        }

        double offsetX = xpos - lastMouseX;
        double offsetY = lastMouseY - ypos;
        
        lastMouseX = xpos;
        lastMouseY = ypos;
        
        if (mouseLookDelegate) {
            mouseLookDelegate(offsetX, offsetY);
        }
    }

    void InputManager::clearDelegates()
    {
        movementDelegate = nullptr;
        mouseLookDelegate = nullptr;
        actionDelegates.clear();
    }

}
