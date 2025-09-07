#pragma once

#include "Lights.h"
#include "object/Shader.h"
#include "core/Camera.h"
#include <glad/glad.h>

Lights::Lights() {
    // Initialize directional light
    dirLight.direction = glm::vec3(0.0f, -1.0f, 1.0f);
    dirLight.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    dirLight.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
    dirLight.specular = glm::vec3(0.5f, 0.5f, 0.5f);

    // Initialize point light properties
    pointLightPosition = glm::vec3(2.0f, 2.0f, -2.0f);
    pointLightAmbient = glm::vec3(0.1f);
    pointLightDiffuse = glm::vec3(0.5f);
    pointLightSpecular = glm::vec3(1.0f);
    pointLightConstant = 1.0f;
    pointLightLinear = 0.09f;
    pointLightQuadratic = 0.032f;

    // Initialize shaders
    lightsShader = std::make_shared<Shader>();
    gizmoShader = std::make_shared<Shader>();

    setupShaders();
    setupLightGizmo();
}

Lights::~Lights() {
    if (lightGizmoVAO != 0) {
        glDeleteVertexArrays(1, &lightGizmoVAO);
    }
}

void Lights::setDirectionalLight(const DirLight& light) {
    dirLight = light;
}

void Lights::setPointLightPosition(const glm::vec3& position) {
    pointLightPosition = position;
    lightGizmoTransform.location = position;
}

void Lights::setupShaders() {
    lightsShader->load("lights.vert", "lights.frag");
    gizmoShader->load("solidcolor.vert", "solidcolor.frag");
}

void Lights::setupLightGizmo() {
    // Set up light gizmo transform
    lightGizmoTransform.location = pointLightPosition;
    lightGizmoTransform.scale = glm::vec3(0.2f, 0.2f, 0.2f); // Small sphere

    // Create a simple sphere for the light gizmo
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Generate sphere vertices (simplified - using icosphere approach)
    const float PI = 3.14159265359f;
    const int segments = 16;
    const int rings = 8;

    // Generate vertices
    for (int i = 0; i <= rings; ++i) {
        float v = (float)i / rings;
        float phi = v * PI;

        for (int j = 0; j <= segments; ++j) {
            float u = (float)j / segments;
            float theta = u * 2.0f * PI;

            Vertex vertex;
            vertex.position.x = cos(theta) * sin(phi);
            vertex.position.y = cos(phi);
            vertex.position.z = sin(theta) * sin(phi);
            
            // Normal is the same as position for a unit sphere
            vertex.normal = vertex.position;
            
            // Simple UV mapping
            vertex.uv = glm::vec2(u, v);
            
            vertices.push_back(vertex);
        }
    }

    // Generate indices
    for (int i = 0; i < rings; ++i) {
        for (int j = 0; j < segments; ++j) {
            int first = i * (segments + 1) + j;
            int second = first + segments + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    // Create VAO, VBO, EBO
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &lightGizmoVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(lightGizmoVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Set vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
}

void Lights::renderLightGizmo(Camera* camera) {
    if (!camera) return;

    glm::mat4 projection = camera->getProjectionMatrix();
    glm::mat4 view = camera->getViewMatrix();

    gizmoShader->use();
    
    // Set up matrices
    gizmoShader->setMat4("view", view);
    gizmoShader->setMat4("projection", projection);
    gizmoShader->setMat4("model", lightGizmoTransform.to_mat4());
    
    // Set light color (bright yellow to represent the light)
    gizmoShader->setVec3("color", glm::vec3(1.0f, 1.0f, 0.0f)); // Yellow
    gizmoShader->setFloat("color_alpha", 1.0f);
    gizmoShader->setFloat("roughness", 0.0f);
    gizmoShader->setFloat("metallic", 0.0f);
    
    // Create a simple white texture for the gizmo
    static GLuint gizmoTexture = 0;
    if (gizmoTexture == 0) {
        glGenTextures(1, &gizmoTexture);
        glBindTexture(GL_TEXTURE_2D, gizmoTexture);
        unsigned char whitePixel[] = {255, 255, 255, 255};
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gizmoTexture);
    gizmoShader->setInt("texture1", 0);

    // Draw the light gizmo
    glBindVertexArray(lightGizmoVAO);
    glDrawElements(GL_TRIANGLES, 16 * 8 * 6, GL_UNSIGNED_INT, 0); // segments * rings * 6 indices per quad
    glBindVertexArray(0);
}

void Lights::setLightUniforms(Shader& shader, Camera* camera) {
    if (!camera) return;

    glm::mat4 projection = camera->getProjectionMatrix();
    glm::mat4 view = camera->getViewMatrix();
    glm::vec3 viewPos = camera->getLocation();

    shader.use();
    
    // Set up camera uniforms
    shader.setMat4("view", view);
    shader.setVec3("viewPos", viewPos);
    shader.setMat4("projection", projection);
    
    // Set up material properties
    shader.setFloat("material.shininess", 32.0f);
    
    // Set up directional light
    shader.setVec3("dirLight.direction", dirLight.direction);
    shader.setVec3("dirLight.ambient", dirLight.ambient);
    shader.setVec3("dirLight.diffuse", dirLight.diffuse);
    shader.setVec3("dirLight.specular", dirLight.specular);
    
    // Set up point light
    shader.setVec3("pointLights[0].position", pointLightPosition);
    shader.setVec3("pointLights[0].ambient", pointLightAmbient);
    shader.setVec3("pointLights[0].diffuse", pointLightDiffuse);
    shader.setVec3("pointLights[0].specular", pointLightSpecular);
    shader.setFloat("pointLights[0].constant", pointLightConstant);
    shader.setFloat("pointLights[0].linear", pointLightLinear);
    shader.setFloat("pointLights[0].quadratic", pointLightQuadratic);
    
    // Set up material textures
    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 1);
}
