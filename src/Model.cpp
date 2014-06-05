#include "Model.hpp"

Model::Model(const std::string &path)
{
  if (load(path) == false)
    throw std::runtime_error("Can't load model : " + path);
}

void Model::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  gdl::Model::draw(*shader, getTransformation(), clock.getElapsed());
}
