#include "Cube6Face.hpp"

Cube6Face::Cube6Face()
  : AGeometry::AGeometry("cube6Face.geo")
{
  glm::vec3 vertice[] = {
    glm::vec3(-1.000000, 1.000000, 1.000000),
    glm::vec3(-1.000000, -1.000000, 1.000000),
    glm::vec3(1.000000, -1.000000, 1.000000),
    glm::vec3(1.000000, 1.000000, 1.000000),
    glm::vec3(-1.000000, 1.000000, -1.000000),
    glm::vec3(1.000000, 1.000000, -1.000000),
    glm::vec3(1.000000, -1.000000, -1.000000),
    glm::vec3(-1.000000, -1.000000, -1.000000),
  };

  glm::vec2 uv[] =
  {
    glm::vec2(0, 0.333333333333333),
    glm::vec2(0.25, 0.333333333333333),
    glm::vec2(0.25, 0.666666666666667),
    glm::vec2(0, 0.666666666666667),
    glm::vec2(0.5, 0.333333333333333),
    glm::vec2(0.5, 0.666666666666667),
    glm::vec2(0.25, 0),
    glm::vec2(0.5, 0),
    glm::vec2(0.5, 1),
    glm::vec2(0.25, 1),
    glm::vec2(0.75, 0.333333333333333),
    glm::vec2(0.75, 0.666666666666667),
    glm::vec2(1, 0.333333333333333),
    glm::vec2(1, 0.666666666666667),
  };

  glm::vec3 normals[] = {
    glm::vec3(0.000000, 0.000000, -1.000000),
    glm::vec3(-1.000000, 0.000000, 0.000000),
    glm::vec3(0.000000, 0.000000, 1.000000),
    glm::vec3(0.000001, 0.000000, 1.000000),
    glm::vec3(1.000000, 0.000000, 0.000000),
    glm::vec3(1.000000, 0.000000, 0.000001),
    glm::vec3(0.000000, 1.000000, 0.000000),
    glm::vec3(0.000000, -1.000000, 0.000000)
  };

  pushVertex(vertice[2]).pushUv(uv[5]).pushNormal(normals[1]);
  pushVertex(vertice[3]).pushUv(uv[4]).pushNormal(normals[1]);
  pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[1]);

  pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[1]);
  pushVertex(vertice[1]).pushUv(uv[2]).pushNormal(normals[1]);
  pushVertex(vertice[2]).pushUv(uv[5]).pushNormal(normals[1]);


  pushVertex(vertice[1]).pushUv(uv[2]).pushNormal(normals[0]);
  pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[0]);
  pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);

  pushVertex(vertice[7]).pushUv(uv[3]).pushNormal(normals[0]);
  pushVertex(vertice[1]).pushUv(uv[2]).pushNormal(normals[0]);
  pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);


  pushVertex(vertice[7]).pushUv(uv[13]).pushNormal(normals[2]);
  pushVertex(vertice[4]).pushUv(uv[12]).pushNormal(normals[2]);
  pushVertex(vertice[5]).pushUv(uv[10]).pushNormal(normals[2]);

  pushVertex(vertice[5]).pushUv(uv[10]).pushNormal(normals[3]);
  pushVertex(vertice[6]).pushUv(uv[11]).pushNormal(normals[3]);
  pushVertex(vertice[7]).pushUv(uv[13]).pushNormal(normals[3]);


  pushVertex(vertice[6]).pushUv(uv[11]).pushNormal(normals[4]);
  pushVertex(vertice[5]).pushUv(uv[10]).pushNormal(normals[4]);
  pushVertex(vertice[3]).pushUv(uv[4]).pushNormal(normals[4]);

  pushVertex(vertice[3]).pushUv(uv[4]).pushNormal(normals[5]);
  pushVertex(vertice[2]).pushUv(uv[5]).pushNormal(normals[5]);
  pushVertex(vertice[6]).pushUv(uv[11]).pushNormal(normals[5]);


  pushVertex(vertice[4]).pushUv(uv[6]).pushNormal(normals[6]);
  pushVertex(vertice[3]).pushUv(uv[4]).pushNormal(normals[6]);
  pushVertex(vertice[5]).pushUv(uv[7]).pushNormal(normals[6]);

  pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[6]);
  pushVertex(vertice[3]).pushUv(uv[4]).pushNormal(normals[6]);
  pushVertex(vertice[4]).pushUv(uv[6]).pushNormal(normals[6]);


  pushVertex(vertice[6]).pushUv(uv[8]).pushNormal(normals[7]);
  pushVertex(vertice[2]).pushUv(uv[5]).pushNormal(normals[7]);
  pushVertex(vertice[1]).pushUv(uv[2]).pushNormal(normals[7]);

  pushVertex(vertice[7]).pushUv(uv[9]).pushNormal(normals[7]);
  pushVertex(vertice[6]).pushUv(uv[8]).pushNormal(normals[7]);
  pushVertex(vertice[1]).pushUv(uv[2]).pushNormal(normals[7]);

  build();
}
