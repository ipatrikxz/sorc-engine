#pragma once

#include "Util.h"
#include <memory>

class Shader;
class Camera;

class Lights {

public:
    Lights();
    ~Lights();

    // Light management
    void setDirectionalLight(const DirLight& light);
    const DirLight& getDirectionalLight() const { return dirLight; }
    DirLight& getDirectionalLight() { return dirLight; }
    
    void setPointLightPosition(const glm::vec3& position);
    const glm::vec3& getPointLightPosition() const { return pointLightPosition; }
    
    void setPointLightAmbient(const glm::vec3& ambient) { pointLightAmbient = ambient; }
    const glm::vec3& getPointLightAmbient() const { return pointLightAmbient; }
    
    void setPointLightDiffuse(const glm::vec3& diffuse) { pointLightDiffuse = diffuse; }
    const glm::vec3& getPointLightDiffuse() const { return pointLightDiffuse; }
    
    void setPointLightSpecular(const glm::vec3& specular) { pointLightSpecular = specular; }
    const glm::vec3& getPointLightSpecular() const { return pointLightSpecular; }
    
    void setPointLightConstant(float constant) { pointLightConstant = constant; }
    float getPointLightConstant() const { return pointLightConstant; }
    
    void setPointLightLinear(float linear) { pointLightLinear = linear; }
    float getPointLightLinear() const { return pointLightLinear; }
    
    void setPointLightQuadratic(float quadratic) { pointLightQuadratic = quadratic; }
    float getPointLightQuadratic() const { return pointLightQuadratic; }

    // Rendering
    void setupShaders();
    void setupLightGizmo();
    void renderLightGizmo(Camera* camera);
    void setLightUniforms(Shader& shader, Camera* camera);

    // Shader access
    Shader* getLightsShader() { return lightsShader.get(); }
    Shader* getGizmoShader() { return gizmoShader.get(); }

private:
    // Light properties
    DirLight dirLight;
    glm::vec3 pointLightPosition;
    glm::vec3 pointLightAmbient;
    glm::vec3 pointLightDiffuse;
    glm::vec3 pointLightSpecular;
    float pointLightConstant;
    float pointLightLinear;
    float pointLightQuadratic;

    // Shaders
    std::shared_ptr<Shader> lightsShader;
    std::shared_ptr<Shader> gizmoShader;

    // Light gizmo
    GLuint lightGizmoVAO;
    Transform lightGizmoTransform;
};
