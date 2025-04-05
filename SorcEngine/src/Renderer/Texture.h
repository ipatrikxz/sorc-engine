#pragma once


#include <iostream>
#include <memory>
#include <string>
#include <string_view>

class Texture {
public:

	explicit Texture(const std::string filepath);
	bool Load(const std::string filepath);

};