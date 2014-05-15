#include <iostream>
#include "Bomb.hpp"

Bomb::Bomb(const int x, const int y) : _x(x), _y(y), _vec(0.01, 0.01)
{
  std::cout << _vec.x << std::endl;
  _obj = new Cube(IEntity::WALL);
  _obj->translate(glm::vec3(x, 0, y));
}

Bomb::~Bomb()
{

}

int	Bomb::getPosX() const
{
  return _x;
}

int	Bomb::getPosY() const
{
  return _y;
}

void	Bomb::setPosX(const int x)
{
  _x = x;
}

void	Bomb::setPosY(const int y)
{
  _y = y;
}

AObject *Bomb::getObj()
{
  return _obj;
}
