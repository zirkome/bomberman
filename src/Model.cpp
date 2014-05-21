#include "Model.hpp"

Model::Model(const std::string &path)
  : _path(path)
{

}

bool	Model::initialize()
{
  if (load(_path) == false)
    return false;
  setCurrentAnim(0);
  return true;
}

void Model::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  gdl::Model::draw(*shader, getTransformation(), clock.getElapsed());
}
