#include "Ground.hpp"
#include "Pan.hpp"

Ground::Ground(const int x, const int y) : _x(x), _y(y)
{
  _obj = new Pan(IEntity::GROUND);
  _obj->translate(glm::vec3(x, 0, y));
}

Ground::~Ground()
{

}

int	Ground::getPosX() const
{
  return _x;
}

int	Ground::getPosY() const
{
  return _y;
}

void	Ground::setPosX(const int x)
{
  _x = x;
}

void	Ground::setPosY(const int y)
{
  _y = y;
}

AObject	*Ground::getObj()
{
  return _obj;
}

void Ground::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{

}
