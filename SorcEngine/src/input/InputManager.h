#pragma once

#include <iostream>	
#include <unordered_map>
#include <functional>
#include <glm/glm.hpp>

namespace window {
    class RenderWindow;
}

class Camera;

namespace input 
{

    // Type aliases for delegates
    using MovementDelegate = std::function<void(float deltaTime, const glm::vec3& inputVector)>;
    using MouseLookDelegate = std::function<void(double offsetX, double offsetY)>;
    using ActionDelegate = std::function<void()>;

	/* 
    * InputManager 
    * 
    */
    class InputManager 
    {

    public:

        InputManager() : deltaTime(0.0f), lastMouseX(0), lastMouseY(0) {}

		~InputManager() = default;

        void processInput(window::RenderWindow& window);
        void handleMouseMovement(double xpos, double ypos);

        void setDeltaTime(float dt) { deltaTime = dt; }

        // Clear all delegates
        void clearDelegates();

        // Delegate registration methods
        void setMovementDelegate(MovementDelegate delegate) { movementDelegate = delegate; }
        void setMouseLookDelegate(MouseLookDelegate delegate) { mouseLookDelegate = delegate; }
        void setActionDelegate(const std::string& action, ActionDelegate delegate) { actionDelegates[action] = delegate; }

    private:

        float deltaTime;
        
		// mouse tracking
        double lastMouseY;
        double lastMouseX;

        // Delegates
        MovementDelegate movementDelegate;
        MouseLookDelegate mouseLookDelegate;
        std::unordered_map<std::string, ActionDelegate> actionDelegates;
    };
}