#include "config.h"
#include "Player.hpp"

Player::Player(const glm::vec2 pos)
  : _vec(pos)
{
  _obj = new Model(RES_ASSETS "marvin.fbx");
  _obj->initialize();
  _obj->translate(glm::vec3(pos.x, -0.5, pos.y));
  _obj->scale(glm::vec3(0.0025, 0.0025, 0.0025));
}

Player::~Player()
{
}

const glm::vec2	&Player::getPos() const
{
  return _vec;
}

void	Player::setPos(const glm::vec2 &new_pos)
{
  _vec = new_pos;
}

void	Player::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{

}

void	Player::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  _obj->draw(shader, clock);
}
