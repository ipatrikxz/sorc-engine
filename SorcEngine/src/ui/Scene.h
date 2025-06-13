#pragma once

#include "Util.hpp"
#include "core/Camera.h"
#include "render/Mesh.h"
//#include "Light.h"

class Shader;

namespace ui 
{

    class Scene {

    public:
        
        Scene();
        
        void init();
        void render();
        void loadMesh(const std::string& filepath);

        Camera* getCamera() { return camera.get(); }
        Shader* getActiveShader() { return activeShader.get(); }
        Mesh* getActiveMesh() { return activeMesh.get(); }

    private:

        void setupFloor();

        void drawMesh();
        void drawFloor();

		// camera
        std::shared_ptr<Camera> camera;
        
		sTransform meshTransform;

        // mesh
        std::shared_ptr<Mesh> activeMesh;
        std::shared_ptr<Shader> activeShader;

        // floor
        GLuint floorVAO;
        sTransform floorTransform;
        std::shared_ptr<Shader> floorShader;

		glm::vec3 lightPosition;
		glm::vec3 lightColor;

    };

}