#include "Box.hpp"

Box::Box(const int x, const int y) : _x(x), _y(y)
{

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
