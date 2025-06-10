#pragma once

#include <string>
#include "SceneViewport.h"

struct GLFWwindow;

namespace nWindow {

    // IWindow Interface
    class IWindow
    {
    public:
        
        virtual void* GetNativeWindow() = 0;
        
        virtual void SetNativeWindow(void* window) = 0;
    };

    // GL window
    class GL_Window : public IWindow {

    public:
        GL_Window(int width, int height, const std::string& title);
        
        // IWindow interface
        void* GetNativeWindow() override { return gl_window; }
        void SetNativeWindow(void* window) { gl_window = (GLFWwindow*)window; }

        // Core
        bool Init();
        void Render();
        void SwapBuffersPollEvents();
        void Cleanup();

        bool IsOpen();
        void SetShouldClose(bool value);
        void SetInputMode(int mode, int value);
        void GetFramebufferSize(int& width, int& height);

    private:
        GLFWwindow* gl_window;
        std::string _title;
        int _width;
        int _height;

        std::unique_ptr<SceneRenderer> scene_viewport;

        bool Init_GL();
    };

}
