#pragma once

#include "Mesh.h"
#include <string>
#include <vector>

class Model {

public:
    Model(const std::string& path);
    void Draw(Shader& shader);
    void LoadModel(const std::string& path);

private:
    std::vector<Mesh> meshes;
    std::string directory; // Store model directory for texture paths


};