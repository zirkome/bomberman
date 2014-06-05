#include <iostream>
#include <stdexcept>

#include "TextureLoader.hpp"

SharedPointer<gdl::Texture> TextureLoader::loadFromFile(const std::string& path)
{
    SharedPointer<gdl::Texture> ptr(new gdl::Texture);

    if (ptr->load(path) == false)
        throw std::runtime_error("Can't load texture : " + path);
    else
        std::cout << path + " has been loaded" << std::endl;

    return ptr;
}
