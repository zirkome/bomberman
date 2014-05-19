#include <iostream>
#include "Bomb.hpp"

Bomb::Bomb(glm::vec2 pos) : _vec(pos)
{
  _obj = new Cube();
  _obj->initialize();
  _obj->translate(glm::vec3(pos.x, 0, pos.y));
}

Bomb::~Bomb()
{

}

glm::vec2	Bomb::getPos() const
{
  return _vec;
}

void	Bomb::setPos(glm::vec2 new_pos)
{
  _vec = new_pos;
}

void	Bomb::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{

}

void    Bomb::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  // _texture->bind();
  _obj->draw(shader, clock);
}
