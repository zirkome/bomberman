#include "Cube.hpp"
#include "config.h"

static gdl::Geometry* geometry = NULL;

Cube::Cube(gdl::Geometry* geometry)
{
  _geometry = geometry;
}

Cube::Cube(const Cube& c)
  : AObject::AObject(c), _geometry(c._geometry)
{
}

const Cube& Cube::operator=(const Cube& c)
{
  _geometry = c._geometry;
  return *this;
}

Cube::Cube()
{
  if (!geometry)
    {

      geometry = new gdl::Geometry;
      _geometry = geometry;

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

      _geometry->pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);
      _geometry->pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[0]);
      _geometry->pushVertex(vertice[3]).pushUv(uv[2]).pushNormal(normals[0]);
      _geometry->pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);
      _geometry->pushVertex(vertice[3]).pushUv(uv[2]).pushNormal(normals[0]);
      _geometry->pushVertex(vertice[7]).pushUv(uv[3]).pushNormal(normals[0]);

      _geometry->pushVertex(vertice[2]).pushUv(uv[0]).pushNormal(normals[1]);
      _geometry->pushVertex(vertice[6]).pushUv(uv[1]).pushNormal(normals[1]);
      _geometry->pushVertex(vertice[7]).pushUv(uv[2]).pushNormal(normals[1]);
      _geometry->pushVertex(vertice[2]).pushUv(uv[0]).pushNormal(normals[1]);
      _geometry->pushVertex(vertice[7]).pushUv(uv[2]).pushNormal(normals[1]);
      _geometry->pushVertex(vertice[3]).pushUv(uv[3]).pushNormal(normals[1]);

      _geometry->pushVertex(vertice[1]).pushUv(uv[0]).pushNormal(normals[2]);
      _geometry->pushVertex(vertice[5]).pushUv(uv[1]).pushNormal(normals[2]);
      _geometry->pushVertex(vertice[2]).pushUv(uv[3]).pushNormal(normals[2]);
      _geometry->pushVertex(vertice[5]).pushUv(uv[1]).pushNormal(normals[3]);
      _geometry->pushVertex(vertice[6]).pushUv(uv[2]).pushNormal(normals[3]);
      _geometry->pushVertex(vertice[2]).pushUv(uv[3]).pushNormal(normals[3]);

      _geometry->pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[4]);
      _geometry->pushVertex(vertice[4]).pushUv(uv[1]).pushNormal(normals[4]);
      _geometry->pushVertex(vertice[1]).pushUv(uv[3]).pushNormal(normals[4]);
      _geometry->pushVertex(vertice[4]).pushUv(uv[1]).pushNormal(normals[5]);
      _geometry->pushVertex(vertice[5]).pushUv(uv[2]).pushNormal(normals[5]);
      _geometry->pushVertex(vertice[1]).pushUv(uv[3]).pushNormal(normals[5]);

      _geometry->pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[6]);
      _geometry->pushVertex(vertice[7]).pushUv(uv[1]).pushNormal(normals[6]);
      _geometry->pushVertex(vertice[5]).pushUv(uv[3]).pushNormal(normals[6]);
      _geometry->pushVertex(vertice[7]).pushUv(uv[1]).pushNormal(normals[6]);
      _geometry->pushVertex(vertice[6]).pushUv(uv[2]).pushNormal(normals[6]);
      _geometry->pushVertex(vertice[5]).pushUv(uv[3]).pushNormal(normals[6]);

      _geometry->pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[7]);
      _geometry->pushVertex(vertice[1]).pushUv(uv[1]).pushNormal(normals[7]);
      _geometry->pushVertex(vertice[2]).pushUv(uv[2]).pushNormal(normals[7]);
      _geometry->pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[7]);
      _geometry->pushVertex(vertice[2]).pushUv(uv[2]).pushNormal(normals[7]);
      _geometry->pushVertex(vertice[3]).pushUv(uv[3]).pushNormal(normals[7]);

      _geometry->build();
    }
  _geometry = geometry;
}

Cube::Cube(const glm::vec4 &color)
{
  if (!geometry)
    {

      geometry = new gdl::Geometry;
      _geometry = geometry;

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

      _geometry->setColor(color);

      _geometry->pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);
      _geometry->pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[0]);
      _geometry->pushVertex(vertice[3]).pushUv(uv[2]).pushNormal(normals[0]);
      _geometry->pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);
      _geometry->pushVertex(vertice[3]).pushUv(uv[2]).pushNormal(normals[0]);
      _geometry->pushVertex(vertice[7]).pushUv(uv[3]).pushNormal(normals[0]);

      _geometry->setColor(color);

      _geometry->pushVertex(vertice[2]).pushUv(uv[0]).pushNormal(normals[1]);
      _geometry->pushVertex(vertice[6]).pushUv(uv[1]).pushNormal(normals[1]);
      _geometry->pushVertex(vertice[7]).pushUv(uv[2]).pushNormal(normals[1]);
      _geometry->pushVertex(vertice[2]).pushUv(uv[0]).pushNormal(normals[1]);
      _geometry->pushVertex(vertice[7]).pushUv(uv[2]).pushNormal(normals[1]);
      _geometry->pushVertex(vertice[3]).pushUv(uv[3]).pushNormal(normals[1]);

      _geometry->setColor(color);

      _geometry->pushVertex(vertice[1]).pushUv(uv[0]).pushNormal(normals[2]);
      _geometry->pushVertex(vertice[5]).pushUv(uv[1]).pushNormal(normals[2]);
      _geometry->pushVertex(vertice[2]).pushUv(uv[3]).pushNormal(normals[2]);
      _geometry->pushVertex(vertice[5]).pushUv(uv[1]).pushNormal(normals[3]);
      _geometry->pushVertex(vertice[6]).pushUv(uv[2]).pushNormal(normals[3]);
      _geometry->pushVertex(vertice[2]).pushUv(uv[3]).pushNormal(normals[3]);

      _geometry->setColor(color);

      _geometry->pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[4]);
      _geometry->pushVertex(vertice[4]).pushUv(uv[1]).pushNormal(normals[4]);
      _geometry->pushVertex(vertice[1]).pushUv(uv[3]).pushNormal(normals[4]);
      _geometry->pushVertex(vertice[4]).pushUv(uv[1]).pushNormal(normals[5]);
      _geometry->pushVertex(vertice[5]).pushUv(uv[2]).pushNormal(normals[5]);
      _geometry->pushVertex(vertice[1]).pushUv(uv[3]).pushNormal(normals[5]);

      _geometry->setColor(color);

      _geometry->pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[6]);
      _geometry->pushVertex(vertice[7]).pushUv(uv[1]).pushNormal(normals[6]);
      _geometry->pushVertex(vertice[5]).pushUv(uv[3]).pushNormal(normals[6]);
      _geometry->pushVertex(vertice[7]).pushUv(uv[1]).pushNormal(normals[6]);
      _geometry->pushVertex(vertice[6]).pushUv(uv[2]).pushNormal(normals[6]);
      _geometry->pushVertex(vertice[5]).pushUv(uv[3]).pushNormal(normals[6]);

      _geometry->setColor(color);

      _geometry->pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[7]);
      _geometry->pushVertex(vertice[1]).pushUv(uv[1]).pushNormal(normals[7]);
      _geometry->pushVertex(vertice[2]).pushUv(uv[2]).pushNormal(normals[7]);
      _geometry->pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[7]);
      _geometry->pushVertex(vertice[2]).pushUv(uv[2]).pushNormal(normals[7]);
      _geometry->pushVertex(vertice[3]).pushUv(uv[3]).pushNormal(normals[7]);

      _geometry->build();
    }
  _geometry = geometry;
}

Cube::~Cube()
{
}

void Cube::draw(gdl::AShader *shader, UNUSED const gdl::Clock &clock)
{
  _geometry->draw(*shader, getTransformation(), GL_TRIANGLES);
}
