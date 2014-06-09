#include "TextureLoader.hpp"

#include <iostream>
#include <stdexcept>

Texture *TextureLoader::loadFromFile(const std::string& path)
{
  Texture *ptr = new Texture(path);

  std::cout << path + " has been loaded" << std::endl;

  return ptr;
}
