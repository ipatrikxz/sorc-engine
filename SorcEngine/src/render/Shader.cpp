#pragma once

#include "Shader.h"
#include "Util.hpp"

int checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "Shader compilation error: " << type << "\n" << infoLog << "\n";
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "Shader linking error: " << type << "\n" << infoLog << "\n";
        }
    }
    return success;
}

bool Shader::load(std::string vertexPath, std::string fragmentPath)
{
    // Read shader source files
    std::string vertexSource = Util::ReadTextFromFile("res/shaders/" + vertexPath);
    std::string fragmentSource = Util::ReadTextFromFile("res/shaders/" + fragmentPath);

    // Check if files were read successfully
    if (vertexSource.empty()) {
        std::cerr << "ERROR::SHADER::VERTEX::FILE_NOT_READ: " << vertexPath << std::endl;
        return false;
    }

    if (fragmentSource.empty()) {
        std::cerr << "ERROR::SHADER::FRAGMENT::FILE_NOT_READ: " << fragmentPath << std::endl;
        return false;
    }

    const char* vShaderCode = vertexSource.c_str();
    const char* fShaderCode = fragmentSource.c_str();

    // Compile vertex shader
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    if (!checkCompileErrors(vertex, "VERTEX")) {
        glDeleteShader(vertex);
        return false;
    }

    // Compile fragment shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    if (!checkCompileErrors(fragment, "FRAGMENT")) 
    {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return false;
    }

    // Link program
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    if (!checkCompileErrors(program, "PROGRAM")) 
    {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(program);
        return false;
    }

    // Clean up old program if it exists
    if (_ID != 0) {
        glDeleteProgram(_ID);
    }

    // Store new program ID
    _ID = program;

    // Clean up shaders (they're linked into program now)
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    std::cout << "Shader loaded successfully: " << vertexPath << ", " << fragmentPath << std::endl;
    return true;
}

void Shader::use()
{
    glUseProgram(_ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(_ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}