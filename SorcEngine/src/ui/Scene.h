#pragma once

#include "render/Shader.h"
#include "render/Model.h"
#include "core/Camera.h"
//#include "Light.h"

class Camera;

namespace ui 
{

    class Scene
    {

    public:
        
        Scene();
        
        void init();
        void render();
        void drawModel(render::Model& model, Shader& shader, glm::mat4 transform);
        void loadModel(const std::string& filepath);

        void setupFloor();
        void drawFloor();

        //std::shared_ptr<Light> getLight() { return light; }
        
        std::shared_ptr<Camera> getCamera() { return camera; }
        std::shared_ptr<render::Model> getActiveModel() { return activeModel; }
        std::shared_ptr<Shader> getActiveShader() { return activeShader; }

    private:

        GLuint floorVAO = 0;
        
        std::shared_ptr<Camera> camera;
        
        //std::shared_ptr<Light> light;

        std::shared_ptr<render::Model> activeModel;
        Transform modelTransform;
        
        std::shared_ptr<Shader> activeShader;
    };

}