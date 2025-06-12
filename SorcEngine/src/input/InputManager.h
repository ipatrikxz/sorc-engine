#pragma once

#include <functional>
#include <unordered_map>
#include <string>

namespace window {
    class RenderWindow;
}

namespace input 
{

    class InputManager 
    {

    public:
        
        void processInput(window::RenderWindow& window);
        void bindAction(const std::string& action, std::function<void(float)> callback);
        void setDeltaTime(float dt) { deltaTime = dt; }

    private:

        std::unordered_map<std::string, std::function<void(float)>> actionCallbacks;

        float deltaTime;
    };
}