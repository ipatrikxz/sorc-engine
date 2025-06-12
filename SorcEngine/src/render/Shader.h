#pragma once

#include <string>
#include <glm/glm.hpp>

/*
*	Shader
*
*	Manages shader compilation, linking, error checking, and uniform setting.
*	It loads vertex and fragment shaders from files,
*	compiles them, links them into a shader program,
*	and stores uniform locations for efficient access.
* 
*/
class Shader 
{
public:
    // the program ID
    int _ID = -1;

    bool load(std::string vertexPath, std::string fragmentPath);
    void use();
    
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value);
    void setVec3(const std::string& name, const glm::vec3& value);
};
