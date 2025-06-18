#pragma once

#include "Util.hpp"
//#include "Light.h"

class Camera;
class Shader;
class Model;
class Mesh;

namespace ui 
{

    class Scene {

    public:
        
        Scene();
        
        void render();

        void loadModel(const std::string& filepath);
		void loadTexture(const std::string& filepath);

        Camera* getCamera() { return camera.get(); }
		Shader* getLightsShader() { return lightsShader.get(); }
		Model* getActiveModel() { return activeModel.get(); }
        DirLight& getDirLight() { return dirLight; }

		void setDirLight(const DirLight& light) { dirLight = light; }

    private:

        void setupFloor();

        void drawMesh();
        void drawFloor();

		// camera
        std::shared_ptr<Camera> camera;

        // model
        std::shared_ptr<Model> activeModel;
		Transform modelTransform;

        // floor
        GLuint floorVAO;
        Transform floorTransform;

        // lights
		DirLight dirLight;
        std::shared_ptr<Shader> lightsShader;

    };

}