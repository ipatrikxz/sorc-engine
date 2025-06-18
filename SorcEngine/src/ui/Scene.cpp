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
        lightsShader = std::make_shared<Shader>();

		modelTransform.location = glm::vec3(0.0f, 1.0f, 0.0f);
		modelTransform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

		dirLight.direction = glm::vec3(0.0f, -1.0f, 1.0f);
		dirLight.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		dirLight.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		dirLight.specular = glm::vec3(0.5f, 0.5f, 0.5f);

        lightsShader->load("lights.vert", "lights.frag");
        loadModel("res/models/Sphere.obj");
        setupFloor();
    }

    void Scene::render() 
    {	
        drawMesh();
        drawFloor();
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
		Material material = activeModel->getMeshes()[0]->getMaterial();

        glm::mat4 projection = camera->getProjectionMatrix();
        glm::mat4 view = camera->getViewMatrix();
        glm::vec3 viewPos = camera->getLocation();

        lightsShader->use();
        // camera
        lightsShader->setMat4("view", view);
        lightsShader->setVec3("viewPos", viewPos);
        lightsShader->setMat4("projection", projection);
        // material
        lightsShader->setFloat("material.shininess", 32.0f);
		// directional light
        lightsShader->setVec3("dirLight.direction", dirLight.direction);
        lightsShader->setVec3("dirLight.ambient", dirLight.ambient);
        lightsShader->setVec3("dirLight.diffuse", dirLight.diffuse);
        lightsShader->setVec3("dirLight.specular", dirLight.specular);
		// transforms
        lightsShader->setMat4("model", modelTransform.to_mat4());
        lightsShader->setInt("material.diffuse", 0);
        lightsShader->setInt("material.specular", 1);
        // Example point light
        lightsShader->setVec3("pointLights[0].position",    glm::vec3(2.0f, 2.0f, -2.0f));
        lightsShader->setVec3("pointLights[0].ambient",     glm::vec3(0.1f));
        lightsShader->setVec3("pointLights[0].diffuse",     glm::vec3(0.5f));
        lightsShader->setVec3("pointLights[0].specular",    glm::vec3(1.0f));
        lightsShader->setFloat("pointLights[0].constant",   1.0f);
        lightsShader->setFloat("pointLights[0].linear",     0.09f);
        lightsShader->setFloat("pointLights[0].quadratic",  0.032f);

        activeModel->draw(*lightsShader);
    }

    void Scene::drawFloor() 
    {
        glm::mat4 projection = camera->getProjectionMatrix();
        glm::mat4 view = camera->getViewMatrix();

        lightsShader->use();
        lightsShader->setMat4("model", floorTransform.to_mat4());

		// draw the floor
        glBindVertexArray(floorVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Scene::setupFloor()
    {
        floorTransform.location = glm::vec3(0.0f, 0.0f, -2.0f);
        floorTransform.scale = glm::vec3(25.0f, 25.0f, 1.0f);
        floorTransform.rotation.x = SORC_PI * -0.5f;

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glBindVertexArray(0);
    }

}