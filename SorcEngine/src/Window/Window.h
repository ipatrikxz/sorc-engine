#pragma once

#include <string>
#include <functional>

struct GLFWwindow;

namespace window 
{
    class RenderWindow 
    {
    
    public:

        RenderWindow();
        ~RenderWindow();

        bool init(int width, int height, const std::string& title);
        void cleanup();
        void swapBuffers();

        void toggleCursor();
        void processEvents();
        bool getIsRunning() const { return isRunning; }
        void* getNativeWindow() const { return windowHandle; }
        void getFramebufferSize(int& width, int& height) const;
        void setShouldClose();

        // Event callbacks
        void setResizeCallback(std::function<void(int, int)> callback) { resizeCallback = callback; }
        void setKeyCallback(std::function<void(int, int, int, int)> callback) { keyCallback = callback; }

    private:

        GLFWwindow* windowHandle;
        int width;
        int height;
        std::string title;
        bool isRunning;
        std::function<void(int, int)> resizeCallback;
        std::function<void(int, int, int, int)> keyCallback;
    };
}
