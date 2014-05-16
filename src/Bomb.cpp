#include <iostream>
#include "Bomb.hpp"

Bomb::Bomb(const float x, const float y) : _vec(x, y)
{
  _obj = new Cube(IEntity::WALL);
  _obj->translate(glm::vec3(x, 0, y));
}

Bomb::~Bomb()
{

}

float	Bomb::getPosX() const
{
  return _vec.x;
}

float	Bomb::getPosY() const
{
  return _vec.y;
}

void	Bomb::setPosX(const float x)
{
  _vec.x = x;
}

void	Bomb::setPosY(const float y)
{
  _vec.y = y;
}

AObject *Bomb::getObj()
{
  return _obj;
}
