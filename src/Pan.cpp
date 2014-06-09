#include "Pan.hpp"

Pan::Pan(const glm::vec2 &repeat)
  : AGeometry::AGeometry("pan.geo")
{
  pushVertex(glm::vec3(1.0f, 1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));
  pushVertex(glm::vec3(-1.0f, 1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));
  pushVertex(glm::vec3(-1.0f, -1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));

  pushVertex(glm::vec3(-1.0f, -1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));
  pushVertex(glm::vec3(1.0f,  -1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));
  pushVertex(glm::vec3(1.0f, 1.0f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, -1.0));

  pushUv(glm::vec2(0.0f, 0.0f));
  pushUv(glm::vec2(repeat.y, 0.0f));
  pushUv(glm::vec2(repeat.y, repeat.x));

  pushUv(glm::vec2(repeat.y, repeat.x));
  pushUv(glm::vec2(0.0f, repeat.x));
  pushUv(glm::vec2(0.0f, 0.0f));

  build();
}