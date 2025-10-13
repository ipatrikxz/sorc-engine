#pragma once
#include <string>

enum TextureType 
{
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT
};

class Texture 
{

private:
    unsigned int ID;

    std::string path;
    std::string name;
    TextureType type;

public:
	
    Texture();

    bool load(std::string filepath);
    unsigned int getID() const { return ID; }

	TextureType getType() const { return type; }
	std::string getPath() const { return path; }
    std::string getName() const { return name; }

    void setType(TextureType textureType) { type = textureType; }
	void setPath(const std::string& filepath) { path = filepath; }
	void setName(const std::string& textureName) { name = textureName; }


};