#include "Box.hpp"

Box::Box(const int x, const int y) : _x(x), _y(y)
{
  _obj = new Cube(IEntity::BOX);
  _obj->translate(glm::vec3(x, 0, y));
}

Box::~Box()
{

}

int	Box::getPosX() const
{
  return _x;
}

int	Box::getPosY() const
{
  return _y;
}

void	Box::setPosX(const int x)
{
  _x = x;
}

void	Box::setPosY(const int y)
{
  _y = y;
}

AObject	*Box::getObj()
{
  return _obj;
}
