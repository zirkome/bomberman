#include "GameGeometry.hpp"
#include "config.h"

GameGeometry::GameGeometry(const SharedPointer<AGeometry>& geo)
  : _geo(geo)
{
}

GameGeometry::GameGeometry(AGeometry* geo)
  : _geo(geo)
{
}

GameGeometry::GameGeometry(const GameGeometry& g)
  : AObject::AObject(g), _geo(g._geo)
{
}

void GameGeometry::draw(gdl::AShader *shader, UNUSED const gdl::Clock& clock)
{
  _geo->draw(*shader, getTransformation(), GL_TRIANGLES);
}

AGeometry* GameGeometry::operator->() const
{
  return _geo.ptr();
}
