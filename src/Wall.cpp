#include "Wall.hpp"
#include "Cube.hpp"

Wall::Wall(const int x, const int y) : _x(x), _y(y)
{
  _obj = new Cube(IEntity::WALL);
  _obj->translate(glm::vec3(x, 0, y));
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

AObject	*Wall::getObj()
{
  return _obj;
}

void Wall::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{

}
