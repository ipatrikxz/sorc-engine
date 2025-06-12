#pragma once

#include "Mesh.h"
#include <string>
#include <vector>

namespace render {

    class Model {

    public:

        Model();
        ~Model() {};

        void draw(Shader& shader);
        void loadModel(const std::string& path);

    private:

        // meshes
        std::vector<Mesh> meshes;

        // model path
        std::string directory; 

    };

}
