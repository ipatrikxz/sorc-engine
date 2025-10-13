#pragma once

#include "Util.h"
#include "light/Lights.h"
#include "render/VertexBuffer.h"
#include <memory>

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
		Shader* getLightsShader() { return lights.getLightsShader(); }
		Model* getActiveModel() { return activeModel.get(); }

		// light management
		Lights& getLights() { return lights; }

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
        std::unique_ptr<render::VertexBuffer> floorVertexBuffer;
        Transform floorTransform;

        // lights
        Lights lights;

    };

}