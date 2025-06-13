#pragma once

#include "Scene.h"

#include <memory>
#include "core/Camera.h"
#include "render/Shader.h"
#include "render/Mesh.h"

namespace ui 
{

    Scene::Scene() 
    {
        camera = std::make_shared<Camera>();
        activeShader = std::make_shared<Shader>();
        floorShader = std::make_shared<Shader>();

		meshTransform.location = glm::vec3(0.0f, 1.0f, 0.0f);
		meshTransform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

        lightPosition = glm::vec3(2.0f, 2.0f, -2.0f);
        lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    void Scene::init()
    {
        floorShader->load("pbr.vert", "pbr.frag");
        activeShader->load("pbr.vert", "pbr.frag");

        loadMesh("res/models/Cube.obj");
        
        setupFloor();
    }

    void Scene::render() 
    {	
        drawFloor();
        drawMesh();
    }

    void Scene::loadMesh(const std::string& filepath) 
    {
        activeMesh = std::make_shared<Mesh>();
        activeMesh->load(filepath);
    }

    void Scene::drawMesh()
    {
		if (!activeMesh) return;
        
        activeMesh->setTransform(meshTransform);
	
        glm::mat4 projection = camera->getProjectionMatrix();
        glm::mat4 view = camera->getViewMatrix();
        glm::vec3 viewPos = camera->getLocation();
  
		activeShader->use();
		// set camera parameters
        activeShader->setMat4("projection", projection);
        activeShader->setMat4("view", view);
        activeShader->setVec3("camPos", viewPos);

        // set light parameters
        activeShader->setVec3("light_position", lightPosition);
        activeShader->setVec3("light_color", lightColor);

        activeMesh->draw(*activeShader);
    }

    void Scene::drawFloor() 
    {
        glm::mat4 projection = camera->getProjectionMatrix();
        glm::mat4 view = camera->getViewMatrix();
        glm::vec3 viewPos = camera->getLocation();

        sMaterial material = {
            glm::vec3(0.7f, 0.7f, 0.7f),    // color
            0.0f,                           // metallic
            0.5f,                           // roughness
            0.2f                            // ao 
        };

        floorShader->use();
        floorShader->setMat4("model", floorTransform.to_mat4());
        floorShader->setMat4("projection", projection);
        floorShader->setMat4("view", view);
        floorShader->setVec3("camPos", viewPos);

        // Set PBR material parameters (no texture for floor)
        floorShader->setVec3("albedo_color", material.color);
        floorShader->setFloat("metallic", material.metallic);
        floorShader->setFloat("roughness", material.roughness);
        floorShader->setFloat("ao", material.ao);

        // Set light properties
        floorShader->setVec3("light_position", lightPosition);
        floorShader->setVec3("light_color", lightColor);

        glBindVertexArray(floorVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Scene::setupFloor()
    {
        floorTransform.location = glm::vec3(0.0f, 0.0f, -2.0f);
        floorTransform.scale = glm::vec3(25.0f, 25.0f, 1.0f);
        floorTransform.rotation.x = SORC_PI * -0.5f;

        std::vector<sVertex> vertices = {
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
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(sVertex), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(sVertex), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(sVertex), (void*)offsetof(sVertex, normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(sVertex), (void*)offsetof(sVertex, uv));
        glBindVertexArray(0);
    }

}