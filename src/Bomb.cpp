#include "Bomb.hpp"

Bomb::Bomb(const int x, const int y) : _x(x), _y(y)
{

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
