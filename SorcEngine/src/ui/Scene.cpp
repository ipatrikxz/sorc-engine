#pragma once

#include "Scene.h"

#include <memory>
#include "core/Camera.h"
#include "object/Shader.h"
#include "object/Mesh.h"
#include "object/Model.h"

enum TextureType;

namespace ui 
{

    Scene::Scene() 
    {
        camera = std::make_shared<Camera>();
        floorVertexBuffer = std::make_unique<render::VertexBuffer>();

		modelTransform.location = glm::vec3(0.0f, 1.0f, 0.0f);
		modelTransform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

        loadModel("res/models/Sphere.obj");
        loadTexture("res/textures/wall.jpg");
        setupFloor();
    }

    void Scene::render() 
    {	
        drawMesh();
        //drawFloor();
        lights.renderLightGizmo(camera.get());
    }

    void Scene::loadModel(const std::string& filepath) 
    {
        activeModel = std::make_shared<Model>();
        activeModel->load(filepath);
    }

    void Scene::loadTexture(const std::string& filepath)
    {
		Model* model = getActiveModel();
        if (!model) return;

		model->loadTexture(filepath);
    }

    void Scene::drawMesh()
    {
		if (!activeModel) return;

        auto& meshes = activeModel->getMeshes();
        if (meshes.empty()) return;
        
        auto& mesh = meshes[0];
        mesh->setTransform(modelTransform);

        // Set up lighting uniforms
        lights.setLightUniforms(*lights.getLightsShader(), camera.get());
        
        // Set model transform
        lights.getLightsShader()->setMat4("model", modelTransform.to_mat4());

        activeModel->draw(*lights.getLightsShader());
    }

    void Scene::drawFloor() 
    {
        // Set up lighting uniforms
        lights.setLightUniforms(*lights.getLightsShader(), camera.get());
        
        // Set up material textures (use default white texture or bind a floor texture)
        lights.getLightsShader()->setInt("material.diffuse", 0);
        lights.getLightsShader()->setInt("material.specular", 1);
        
        // Create and bind a default white texture for diffuse
        static GLuint defaultWhiteTexture = 0;
        if (defaultWhiteTexture == 0) {
            glGenTextures(1, &defaultWhiteTexture);
            glBindTexture(GL_TEXTURE_2D, defaultWhiteTexture);
            unsigned char whitePixel[] = {255, 255, 255, 255};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, defaultWhiteTexture);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, defaultWhiteTexture);
        
        lights.getLightsShader()->setMat4("model", floorTransform.to_mat4());

		// draw the floor
        floorVertexBuffer->draw(6);
    }

    void Scene::setupFloor()
    {
        floorTransform.location = glm::vec3(0.0f, 0.0f, -2.0f);
        floorTransform.scale = glm::vec3(25.0f, 25.0f, 1.0f);
        floorTransform.rotation.x = SORC_PI * -0.5f;

        std::vector<Vertex> vertices = {
            {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},  // top-left
            {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},   // top-right
            {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // bottom-right
            {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}   // bottom-left
        };

        std::vector<unsigned int> indices = { 2, 1, 0, 0, 3, 2 };

        floorVertexBuffer->setVertexData(vertices, indices);
    }


}