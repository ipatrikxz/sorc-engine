#pragma once
#include <string>

class Texture {
private:
    unsigned int ID;

public:
    Texture(std::string filepath);
    bool Load(std::string filepath);
    unsigned int GetID() const { return ID; }
};