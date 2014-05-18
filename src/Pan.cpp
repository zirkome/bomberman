#include "Pan.hpp"

Pan::Pan(IEntity::Type assetsType)
{
  _texture = AssetsManager::getInstance()->getAssets<gdl::Texture>(assetsType);
}

Pan::Pan()
{
  _texture = NULL;
}

Pan::~Pan()
{

}

bool Pan::initialize()
{
  _geometry.pushVertex(glm::vec3(1.0f, 1.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(-1.0f, 1.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(-1.0f, -1.0f, 0.0f));

  _geometry.pushVertex(glm::vec3(-1.0f, -1.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(1.0f,  -1.0f, 0.0f));
  _geometry.pushVertex(glm::vec3(1.0f, 1.0f, 0.0f));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));

  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));

  _geometry.build();
  return (true);
}

void Pan::draw(gdl::AShader *shader, UNUSED const gdl::Clock& clock)
{
  if (_texture)
    _texture->bind();
  _geometry.draw(*shader, getTransformation(), GL_TRIANGLES);
}

void Pan::draw(gdl::AShader *shader)
{
  if (_texture)
    _texture->bind();
  _geometry.draw(*shader, getTransformation(), GL_TRIANGLES);
}
