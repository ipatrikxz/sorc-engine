#pragma once

#include <iostream>	
#include <functional>
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

namespace window {
    class RenderWindow;
}
class Camera;

namespace input 
{

    struct sInputAction 
    {
        int key;
        glm::vec3 inputVector;
        std::function<void(float)> callback;
    };

	/* 
    * InputManager class 
    * handles input bindings, actions and callbacks
    * 
    */
    class InputManager 
    {

    public:

        InputManager() : deltaTime(0.0f), lastMouseX(0), lastMouseY(0), camera(nullptr) {}
        ~InputManager() { unbindAndClearInput(); }

        void initInputMap(Camera* camera, const window::RenderWindow& window);
        
        void processInput(window::RenderWindow& window);

        void bindAction(const std::string& action, std::function<void(float)> callback);
        
        void handleMouseMovement(double xpos, double ypos);

        void setDeltaTime(float dt) { deltaTime = dt; }

        void unbindAndClearInput();

    private:

        Camera* camera;

        float deltaTime;
        
		// mouse tracking
        double lastMouseY;
        double lastMouseX;
        
        std::unordered_map<std::string, std::function<void(float)>> actionCallbacks;
        
        std::unordered_map<std::string, sInputAction> inputMap;

        glm::vec3 movementVector = glm::vec3(0.0f);

    };
}