#pragma once

#include "Mesh.h"
#include <string>
#include <vector>

class Model {
private:
    std::vector<Mesh> meshes;

public:
    Model(const std::string& path);
    void Draw(Shader& shader);
    void LoadModel(const std::string& path);
};