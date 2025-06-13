#pragma once

#include "InputManager.h"

#include <functional>
#include <unordered_map>
#include <string>

#include "window/Window.h"
#include "Core/Camera.h"

namespace input 
{
    void InputManager::processInput(window::RenderWindow& window)
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(window.getNativeWindow());

		// reset movement vector each frame
        movementVector = glm::vec3(0.0f);

		// accumulate movement vector based on pressed keys
        for (const auto& [action, mapping] : inputMap) 
        {
            if (glfwGetKey(glfwWindow, mapping.key) == GLFW_PRESS) 
            {
                movementVector += mapping.inputVector;
            }
        }

		// if we have a valid movement vector, call the action callback
        if (glm::length(movementVector) > 0.0f && actionCallbacks.count("moveCamera")) 
        {
            actionCallbacks["moveCamera"](deltaTime);
        }

		// close window on ESC key press
        if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        {
            window.setShouldClose();
        }

		// mouse input handling                
        if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
			// Capture mouse position
            glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CENTER_CURSOR);
            double mouseX, mouseY;
            glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);
			handleMouseMovement(mouseX, mouseY);
        }
        
        if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
        {
            glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    void InputManager::handleMouseMovement(double xpos, double ypos)
    {
        if (lastMouseX != 0 || lastMouseY != 0)
        {
            double offsetX = xpos - lastMouseX;
            double offsetY = lastMouseY - ypos;

            lastMouseX = xpos;
            lastMouseY = ypos;

            // Apply rotation to camera
            camera->lookCamera(offsetX, offsetY);
        }
        else
        {
			lastMouseX = 0;
			lastMouseY = 0;
        }

        lastMouseX = xpos;
        lastMouseY = ypos;
    }

    void InputManager::initInputMap(Camera* camera, const window::RenderWindow& window)
    {
        if (!camera)
        {
            std::cerr << "Error: Camera was null during input initInputMap() \n";
            return;
        }

        // cache the camera
		this->camera = camera;

		// movement directions - TODO : hide this further
        inputMap["forward"]         = { GLFW_KEY_W, glm::vec3(0.0f, 0.0f, 1.0f),    nullptr };
        inputMap["backward"]        = { GLFW_KEY_S, glm::vec3(0.0f, 0.0f, -1.0f),   nullptr };
        inputMap["right"]           = { GLFW_KEY_D, glm::vec3(1.0f, 0.0f, 0.0f),    nullptr };
        inputMap["left"]            = { GLFW_KEY_A, glm::vec3(-1.0f, 0.0f, 0.0f),   nullptr };
        inputMap["up"]              = { GLFW_KEY_E, glm::vec3(0.0f, 1.0f, 0.0f),    nullptr };
        inputMap["down"]            = { GLFW_KEY_Q, glm::vec3(0.0f, -1.0f, 0.0f),   nullptr };

        // bind moveCamera action
        if (!actionCallbacks.count("moveCamera")) 
        {
            actionCallbacks["moveCamera"] = [camera, this](float dt) 
            {
                glm::vec3 worldDir = (
                    camera->getFront() * movementVector.z +
                    camera->getRight() * movementVector.x +
                    camera->getUp() * movementVector.y
                );
                
				// If the length of the direction is greater than zero, we can move
                if (glm::length(worldDir) > 0.0f)
                {
                    worldDir = glm::normalize(worldDir);
                    // finally move the camera
                    camera->moveCamera(dt, worldDir);
                }
            };
        }
    }

    void InputManager::bindAction(const std::string& action, std::function<void(float)> callback) 
    {
        actionCallbacks[action] = callback;
    }

    void InputManager::unbindAndClearInput()
    {
		actionCallbacks.clear();
        inputMap.clear();
    }


}
