#include <iostream>
#include <stdexcept>

#include "ModelLoader.hpp"
#include "Model.hpp"

bomberman::SPModel ModelLoader::loadFromFile(const std::string& path)
{
    bomberman::SPModel ptr(new Model(path));

    std::cout << path + " has been loaded" << std::endl;

    return ptr;
}
