#include "Ground.hpp"
#include "Plan.hpp"

Ground::Ground(const float x, const float y) : _vec(x, y)
{
  _obj = new Plan(IEntity::GROUND);
  _obj->translate(glm::vec3(x, 0, y));
}

Ground::~Ground()
{

}

float	Ground::getPosX() const
{
  return _vec.x;
}

float	Ground::getPosY() const
{
  return _vec.y;
}

void	Ground::setPosX(const float x)
{
  _vec.x = x;
}

void	Ground::setPosY(const float y)
{
  _vec.y = y;
}

AObject	*Ground::getObj()
{
  return _obj;
}
