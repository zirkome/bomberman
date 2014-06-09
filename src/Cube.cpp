#include "Cube.hpp"

Cube::Cube()
  : AGeometry::AGeometry("cube.geo")
{
  glm::vec3 vertice[] = {
    glm::vec3(1.000000, -1.000000, -1.000000),
    glm::vec3(1.000000, -1.000000, 1.000000),
    glm::vec3(-1.000000, -1.000000, 1.000000),
    glm::vec3(-1.000000, -1.000000, -1.000000),
    glm::vec3(1.000000, 1.000000, -1.000000),
    glm::vec3(1.000000, 1.000000, 1.000000),
    glm::vec3(-1.000000, 1.000000, 1.000000),
    glm::vec3(-1.000000, 1.000000, -1.000000)
  };

  glm::vec2 uv[] = {
    glm::vec2(0.000000, 0.000000),
    glm::vec2(1.000000, 0.000000),
    glm::vec2(1.000000, 1.000000),
    glm::vec2(0.000000, 1.000000)
  };

  glm::vec3 normals[] = {
    glm::vec3(0.000000, 0.000000, -1.000000),
    glm::vec3(-1.000000, 0.000000, 0.000000),
    glm::vec3(0.000000, 0.000000, 1.000000),
    glm::vec3(0.000000, 0.000000, 1.000000),
    glm::vec3(1.000000, 0.000000, 0.000000),
    glm::vec3(1.000000, 0.000000, 0.000000),
    glm::vec3(0.000000, 1.000000, 0.000000),
    glm::vec3(0.000000, -1.000000, 0.000000)
  };

  pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);
  pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[0]);
  pushVertex(vertice[3]).pushUv(uv[2]).pushNormal(normals[0]);
  pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);
  pushVertex(vertice[3]).pushUv(uv[2]).pushNormal(normals[0]);
  pushVertex(vertice[7]).pushUv(uv[3]).pushNormal(normals[0]);

  pushVertex(vertice[2]).pushUv(uv[0]).pushNormal(normals[1]);
  pushVertex(vertice[6]).pushUv(uv[1]).pushNormal(normals[1]);
  pushVertex(vertice[7]).pushUv(uv[2]).pushNormal(normals[1]);
  pushVertex(vertice[2]).pushUv(uv[0]).pushNormal(normals[1]);
  pushVertex(vertice[7]).pushUv(uv[2]).pushNormal(normals[1]);
  pushVertex(vertice[3]).pushUv(uv[3]).pushNormal(normals[1]);

  pushVertex(vertice[1]).pushUv(uv[0]).pushNormal(normals[2]);
  pushVertex(vertice[5]).pushUv(uv[1]).pushNormal(normals[2]);
  pushVertex(vertice[2]).pushUv(uv[3]).pushNormal(normals[2]);
  pushVertex(vertice[5]).pushUv(uv[1]).pushNormal(normals[3]);
  pushVertex(vertice[6]).pushUv(uv[2]).pushNormal(normals[3]);
  pushVertex(vertice[2]).pushUv(uv[3]).pushNormal(normals[3]);

  pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[4]);
  pushVertex(vertice[4]).pushUv(uv[1]).pushNormal(normals[4]);
  pushVertex(vertice[1]).pushUv(uv[3]).pushNormal(normals[4]);
  pushVertex(vertice[4]).pushUv(uv[1]).pushNormal(normals[5]);
  pushVertex(vertice[5]).pushUv(uv[2]).pushNormal(normals[5]);
  pushVertex(vertice[1]).pushUv(uv[3]).pushNormal(normals[5]);

  pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[6]);
  pushVertex(vertice[7]).pushUv(uv[1]).pushNormal(normals[6]);
  pushVertex(vertice[5]).pushUv(uv[3]).pushNormal(normals[6]);
  pushVertex(vertice[7]).pushUv(uv[1]).pushNormal(normals[6]);
  pushVertex(vertice[6]).pushUv(uv[2]).pushNormal(normals[6]);
  pushVertex(vertice[5]).pushUv(uv[3]).pushNormal(normals[6]);

  pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[7]);
  pushVertex(vertice[1]).pushUv(uv[1]).pushNormal(normals[7]);
  pushVertex(vertice[2]).pushUv(uv[2]).pushNormal(normals[7]);
  pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[7]);
  pushVertex(vertice[2]).pushUv(uv[2]).pushNormal(normals[7]);
  pushVertex(vertice[3]).pushUv(uv[3]).pushNormal(normals[7]);

  build();
}
