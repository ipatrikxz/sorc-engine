#pragma once

#include "Scene.h"

#include <glm/glm.hpp>
#include <memory>

#include "core/Camera.h"
#include "render/Shader.h"
#include "render/Model.h"

namespace ui 
{

    Scene::Scene() 
    {
        camera = std::make_shared<Camera>();
        activeShader = std::make_shared<Shader>();
        //light = std::make_shared<Light>();

        modelTransform.location = glm::vec3(0.0f, 1.0f, 0.0f);
        modelTransform.scale = glm::vec3(1.0f);
    }

    void Scene::init()
    {
        activeShader->load("solidcolor.vert", "solidcolor.frag");
        loadModel("res/models/Cube.obj");
        setupFloor();
    }

    void Scene::render() 
    {
        activeShader->use();
        
        glm::mat4 projection = camera->getProjectionMatrix();
        glm::mat4 view = camera->getViewMatrix();

        activeShader->setMat4("projection", projection);
        activeShader->setMat4("view", view);
        
        if (activeModel)
        {
            drawModel(*activeModel, *activeShader, modelTransform.to_mat4());
        }

		drawFloor();
    }

    void Scene::loadModel(const std::string& filepath) 
    {
        activeModel = std::make_shared<render::Model>();
        activeModel->loadModel(filepath);
    }

    void Scene::drawModel(render::Model& model, Shader& shader, glm::mat4 transform)
    {
		activeShader->setMat4("model", transform);
        activeShader->setVec3("color", WHITE);
        activeModel->draw(*activeShader);
    }

    void Scene::setupFloor() 
    {
        std::vector<Vertex> vertices = {
            {glm::vec3(-0.5f, 0.5f, 0.0f)},
            {glm::vec3(0.5f, 0.5f, 0.0f)},
            {glm::vec3(0.5f, -0.5f, 0.0f)},
            {glm::vec3(-0.5f, -0.5f, 0.0f)}
        };

        std::vector<unsigned int> indices = { 2, 1, 0, 0, 3, 2 };
        unsigned int VBO, EBO;

        glGenVertexArrays(1, &floorVAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(floorVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glBindVertexArray(0);
    }

    void Scene::drawFloor() {
        activeShader->use();
        Transform largeQuad;
        largeQuad.location = glm::vec3(0.0f, 0.0f, 0.0f);
        largeQuad.rotation.x = SORC_PI * -0.5f;
        largeQuad.scale = glm::vec3(25.0f, 25.0f, 1.0f);
        activeShader->setMat4("model", largeQuad.to_mat4());
        activeShader->setVec3("color", DARK);

        glBindVertexArray(floorVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}