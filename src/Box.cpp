#include "Wall.hpp"

Wall::Wall(const int x, const int y) : _x(x), _y(y)
{

}

Wall::~Wall()
{

}

int	Wall::getPosX() const
{
  return _x;
}

int	Wall::getPosY() const
{
  return _y;
}

void	Wall::setPosX(const int x)
{
  _x = x;
}

void	Wall::setPosY(const int y)
{
  _y = y;
}
