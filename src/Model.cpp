#include "Model.hpp"

Model::Model(const std::string &path)
  : _path(path)
{

}

bool	Model::initialize()
{
  _model = new gdl::Model;

  if (_model->load(_path) == false)
    return false;
  _model->setCurrentAnim(0);
  return true;
}

void Model::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  _model->draw(*shader, getTransformation(), clock.getElapsed());
}
