#include <iostream>
#include <stdexcept>

#include "TextureLoader.hpp"
#include "Texture.hpp"

Texture *TextureLoader::loadFromFile(const std::string& path)
{
    Texture *ptr = new Texture(path);

    std::cout << path + " has been loaded" << std::endl;

    return ptr;
}
