#include "Pan.hpp"

Pan::Pan(const glm::vec2 &repeat)
  : _repeat(repeat)
{
}

Pan::~Pan()
{

}

bool Pan::initialize()
{
  _geometry.pushVertex(glm::vec3(1.0f, 1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));
  _geometry.pushVertex(glm::vec3(-1.0f, 1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));
  _geometry.pushVertex(glm::vec3(-1.0f, -1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));

  _geometry.pushVertex(glm::vec3(-1.0f, -1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));
  _geometry.pushVertex(glm::vec3(1.0f,  -1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));
  _geometry.pushVertex(glm::vec3(1.0f, 1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(_repeat.y, 0.0f));
  _geometry.pushUv(glm::vec2(_repeat.y, _repeat.x));

  _geometry.pushUv(glm::vec2(_repeat.y, _repeat.x));
  _geometry.pushUv(glm::vec2(0.0f, _repeat.x));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));

  _geometry.build();
  return (true);
}

void Pan::draw(gdl::AShader *shader, UNUSED const gdl::Clock& clock)
{
  _geometry.draw(*shader, getTransformation(), GL_TRIANGLES);
}

void Pan::draw(gdl::AShader *shader)
{
  _geometry.draw(*shader, getTransformation(), GL_TRIANGLES);
}
