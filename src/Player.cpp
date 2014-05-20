#include "config.h"
#include "Player.hpp"

Player::Player(const glm::vec2 pos, Map *map)
  : _vec(pos), _map(map), _speed(3)
{
  _obj = new Model(RES_ASSETS "marvin.fbx");
  _obj->initialize();
  _obj->translate(glm::vec3(pos.x, -0.2, pos.y));
  _obj->scale(glm::vec3(0.0025, 0.0025, 0.0025));
  _movePtr[SDLK_UP] = &Player::moveUp;
  _movePtr[SDLK_DOWN] = &Player::moveDown;
  _movePtr[SDLK_RIGHT] = &Player::moveRight;
  _movePtr[SDLK_LEFT] = &Player::moveLeft;
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

void	Player::update(gdl::Input &input, gdl::Clock const &clock)
{
  for (MovePtr::const_iterator it = _movePtr.begin(), end = _movePtr.end(); it != end; ++it)
    if (input.getKey(it->first)) {
      (this->*_movePtr[it->first])(clock.getElapsed() * _speed);
      return ;
    }
}

void	Player::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  _obj->draw(shader, clock);
}

bool	Player::moveUp(double const distance)
{
  _vec.y += distance;
  _obj->translate(glm::vec3(0, 0, distance));
  return true;
}

bool	Player::moveDown(double const distance)
{
  _vec.y -= distance;
  _obj->translate(glm::vec3(0, 0, -distance));
  return true;
}

bool	Player::moveLeft(double const distance)
{
  _vec.x += distance;
  _obj->translate(glm::vec3(distance, 0, 0));
  return true;
}

bool	Player::moveRight(double const distance)
{
  _vec.x -= distance;
  _obj->translate(glm::vec3(-distance, 0, 0));
  return true;
}

IEntity::Type Player::getType() const
{
  return IEntity::PLAYER;
}
