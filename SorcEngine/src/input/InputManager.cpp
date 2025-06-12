#include "InputManager.h"

#include <GLFW/glfw3.h>
#include "window/Window.h"

namespace input 
{
    void InputManager::processInput(window::RenderWindow& window)
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(window.getNativeWindow());

        // wasd camera 
        if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS) 
        {
            if (actionCallbacks.count("moveCameraForward")) {
                actionCallbacks["moveCameraForward"](deltaTime);
            }
        }
        if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS) 
        {
            if (actionCallbacks.count("moveCameraBackward")) 
            {
                actionCallbacks["moveCameraBackward"](deltaTime);
            }
        }
        if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        {
            if (actionCallbacks.count("moveCameraRight"))
            {
                actionCallbacks["moveCameraRight"](deltaTime);
            }
        }
        if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        {
            if (actionCallbacks.count("moveCameraLeft"))
            {
                actionCallbacks["moveCameraLeft"](deltaTime);
            }
        }
        if (glfwGetKey(glfwWindow, GLFW_KEY_Q) == GLFW_PRESS)
        {
            if (actionCallbacks.count("moveCameraDown"))
            {
                actionCallbacks["moveCameraDown"](deltaTime);
            }
        }
        if (glfwGetKey(glfwWindow, GLFW_KEY_E) == GLFW_PRESS)
        {
            if (actionCallbacks.count("moveCameraUp"))
            {
                actionCallbacks["moveCameraUp"](deltaTime);
            }
        }

        // utility
        if (glfwGetKey(glfwWindow, GLFW_KEY_O) == GLFW_PRESS) 
        {
            if (actionCallbacks.count("toggleCursor")) 
            {
                actionCallbacks["toggleCursor"](0.0f);
            }
        }
        if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        {
            window.setShouldClose();
        }

        double mouseX, mouseY;
        glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);
        // TODO : Update scene camera mouse cursor
        if (actionCallbacks.count("updateMousePosition")) 
        {
            actionCallbacks["updateMousePosition"](mouseX), (mouseY);
		}
    }

    void InputManager::bindAction(const std::string& action, std::function<void(float)> callback) 
    {
        actionCallbacks[action] = callback;
    }

}
