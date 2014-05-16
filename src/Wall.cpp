#include "Wall.hpp"
#include "Cube.hpp"

Wall::Wall(const float x, const float y) : _vec(x, y)
{
  _obj = new Cube(IEntity::WALL);
  _obj->translate(glm::vec3(x, 0, y));
}

Wall::~Wall()
{

}

float	Wall::getPosX() const
{
  return _vec.x;
}

float	Wall::getPosY() const
{
  return _vec.y;
}

void	Wall::setPosX(const float x)
{
  _vec.x = x;
}

void	Wall::setPosY(const float y)
{
  _vec.y = y;
}

AObject	*Wall::getObj()
{
  return _obj;
}
