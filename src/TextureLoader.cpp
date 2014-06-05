#include <iostream>
#include <stdexcept>

#include "TextureLoader.hpp"
#include "Texture.hpp"

bomberman::SPTexture TextureLoader::loadFromFile(const std::string& path)
{
    bomberman::SPTexture ptr(new Texture(path));

    std::cout << path + " has been loaded" << std::endl;

    return ptr;
}
