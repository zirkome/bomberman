#include "Box.hpp"

Box::Box(const float x, const float y) : _vec(x, y)
{
  _obj = new Cube(IEntity::BOX);
  _obj->translate(glm::vec3(x, 0, y));
}

Box::~Box()
{

}

float	Box::getPosX() const
{
  return _vec.x;
}

float	Box::getPosY() const
{
  return _vec.y;
}

void	Box::setPosX(const float x)
{
  _vec.x = x;
}

void	Box::setPosY(const float y)
{
  _vec.y = y;
}

AObject	*Box::getObj()
{
  return _obj;
}

void Box::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{

}
