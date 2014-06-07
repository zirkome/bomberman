#include <iostream>
#include <stdexcept>

#include "ModelLoader.hpp"
#include "Model.hpp"

Model* ModelLoader::loadFromFile(const std::string& path)
{
  Model *ptr = new Model(path);

  std::cout << path + " has been loaded" << std::endl;

  return ptr;
}
