#include "Cube6Face.hpp"

Cube6Face::Cube6Face(gdl::Geometry* geometry)
  : _geometry(geometry)
{
}

Cube6Face::Cube6Face(const Cube6Face& c)
  : _geometry(c._geometry)
{
}

const Cube6Face& Cube6Face::operator=(const Cube6Face& c)
{
  _geometry = c._geometry;
  return *this;
}

Cube6Face::Cube6Face()
{
  _geometry = new gdl::Geometry;

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

  _geometry->pushVertex(vertice[2]).pushUv(uv[5]).pushNormal(normals[1]);
  _geometry->pushVertex(vertice[3]).pushUv(uv[4]).pushNormal(normals[1]);
  _geometry->pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[1]);

  _geometry->pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[1]);
  _geometry->pushVertex(vertice[1]).pushUv(uv[2]).pushNormal(normals[1]);
  _geometry->pushVertex(vertice[2]).pushUv(uv[5]).pushNormal(normals[1]);


  _geometry->pushVertex(vertice[1]).pushUv(uv[2]).pushNormal(normals[0]);
  _geometry->pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[0]);
  _geometry->pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);

  _geometry->pushVertex(vertice[7]).pushUv(uv[3]).pushNormal(normals[0]);
  _geometry->pushVertex(vertice[1]).pushUv(uv[2]).pushNormal(normals[0]);
  _geometry->pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);


  _geometry->pushVertex(vertice[7]).pushUv(uv[13]).pushNormal(normals[2]);
  _geometry->pushVertex(vertice[4]).pushUv(uv[12]).pushNormal(normals[2]);
  _geometry->pushVertex(vertice[5]).pushUv(uv[10]).pushNormal(normals[2]);

  _geometry->pushVertex(vertice[5]).pushUv(uv[10]).pushNormal(normals[3]);
  _geometry->pushVertex(vertice[6]).pushUv(uv[11]).pushNormal(normals[3]);
  _geometry->pushVertex(vertice[7]).pushUv(uv[13]).pushNormal(normals[3]);


  _geometry->pushVertex(vertice[6]).pushUv(uv[11]).pushNormal(normals[4]);
  _geometry->pushVertex(vertice[5]).pushUv(uv[10]).pushNormal(normals[4]);
  _geometry->pushVertex(vertice[3]).pushUv(uv[4]).pushNormal(normals[4]);

  _geometry->pushVertex(vertice[3]).pushUv(uv[4]).pushNormal(normals[5]);
  _geometry->pushVertex(vertice[2]).pushUv(uv[5]).pushNormal(normals[5]);
  _geometry->pushVertex(vertice[6]).pushUv(uv[11]).pushNormal(normals[5]);


  _geometry->pushVertex(vertice[4]).pushUv(uv[6]).pushNormal(normals[6]);
  _geometry->pushVertex(vertice[3]).pushUv(uv[4]).pushNormal(normals[6]);
  _geometry->pushVertex(vertice[5]).pushUv(uv[7]).pushNormal(normals[6]);

  _geometry->pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[6]);
  _geometry->pushVertex(vertice[3]).pushUv(uv[4]).pushNormal(normals[6]);
  _geometry->pushVertex(vertice[4]).pushUv(uv[6]).pushNormal(normals[6]);


  _geometry->pushVertex(vertice[6]).pushUv(uv[8]).pushNormal(normals[7]);
  _geometry->pushVertex(vertice[2]).pushUv(uv[5]).pushNormal(normals[7]);
  _geometry->pushVertex(vertice[1]).pushUv(uv[2]).pushNormal(normals[7]);

  _geometry->pushVertex(vertice[7]).pushUv(uv[9]).pushNormal(normals[7]);
  _geometry->pushVertex(vertice[6]).pushUv(uv[8]).pushNormal(normals[7]);
  _geometry->pushVertex(vertice[1]).pushUv(uv[2]).pushNormal(normals[7]);

  _geometry->build();
}

void Cube6Face::draw(gdl::AShader *shader, UNUSED const gdl::Clock &clock)
{
  _geometry->draw(*shader, getTransformation(), GL_TRIANGLES);
}
