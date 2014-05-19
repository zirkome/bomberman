#include "Pan.hpp"

Pan::Pan()
{
}

Pan::~Pan()
{

}

bool Pan::initialize()
{
  _geometry.pushVertex(glm::vec3(1.0f, 1.0f, 0.0f)).pushNormal(glm::vec3(0.000000, 0.000000, -1.000000));
  _geometry.pushVertex(glm::vec3(-1.0f, 1.0f, 0.0f)).pushNormal(glm::vec3(0.000000, 0.000000, -1.000000));
  _geometry.pushVertex(glm::vec3(-1.0f, -1.0f, 0.0f)).pushNormal(glm::vec3(0.000000, 0.000000, -1.000000));

  _geometry.pushVertex(glm::vec3(-1.0f, -1.0f, 0.0f)).pushNormal(glm::vec3(0.000000, 0.000000, -1.000000));
  _geometry.pushVertex(glm::vec3(1.0f,  -1.0f, 0.0f)).pushNormal(glm::vec3(0.000000, 0.000000, -1.000000));
  _geometry.pushVertex(glm::vec3(1.0f, 1.0f, 0.0f)).pushNormal(glm::vec3(0.000000, 0.000000, -1.000000));

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
  _geometry.draw(*shader, getTransformation(), GL_TRIANGLES);
}

void Pan::draw(gdl::AShader *shader)
{
  _geometry.draw(*shader, getTransformation(), GL_TRIANGLES);
}
