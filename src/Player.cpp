#include "config.h"
#include "Player.hpp"

Player::Player(const glm::vec2 pos, Map *map)
  : _vec(pos), _map(map), _speed(4), _way(UP), _size(0.7)
{
  _obj = new Model(RES_ASSETS "marvin.fbx");
  _obj->initialize();
  _obj->translate(glm::vec3(pos.x, -0.5, pos.y));
  _obj->scale(glm::vec3(0.0025, 0.0025, 0.0025));
  _movePtr[SDLK_UP] = &Player::moveUp;
  _movePtr[SDLK_DOWN] = &Player::moveDown;
  _movePtr[SDLK_RIGHT] = &Player::moveRight;
  _movePtr[SDLK_LEFT] = &Player::moveLeft;
  _status = STANDBY;

  _obj->createSubAnim(0, "standby", 0, 0);
  _obj->createSubAnim(0, "walk", 42, 63);
  _obj->createSubAnim(0, "stop_walking", 64, 121);
  _obj->setCurrentSubAnim("standby");
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
  bool	hasMoved;

  for (MovePtr::const_iterator it = _movePtr.begin(), end = _movePtr.end(); it != end; ++it)
    if (input.getKey(it->first)) {
      hasMoved = (this->*_movePtr[it->first])(clock.getElapsed() * _speed);
      if (_status != WALK && hasMoved)
	{
	  _status = WALK;
	  _obj->setCurrentSubAnim("walk");
	}
      else if (_status == WALK && !hasMoved)
	{
	  _obj->setCurrentSubAnim("stop_walking", false);
	  _status = STOP_WALK;
	}
      return ;
    }
  if (_status == WALK)
    {
      _obj->setCurrentSubAnim("stop_walking", false);
      _status = STOP_WALK;
    }
}

void	Player::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  _obj->draw(shader, clock);
}

bool	Player::moveUp(double const distance)
{
  double rotate;

  rotate = (_way - UP) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = UP;
  if (_map->getTypeAt(_vec.x + _size, _vec.y + distance + 1) == GROUND &&
      _map->getTypeAt(_vec.x + 1 - _size, _vec.y + distance + 1) == GROUND) {
    _vec.y += distance;
    _obj->translate(glm::vec3(0, 0, distance));
    return true;
  }
  return false;
}

bool	Player::moveDown(double const distance)
{
  double rotate;

  rotate = (_way - DOWN) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = DOWN;
  if (_map->getTypeAt(_vec.x + _size, _vec.y - distance) == GROUND &&
      _map->getTypeAt(_vec.x + 1 - _size, _vec.y - distance) == GROUND) {
    _vec.y -= distance;
    _obj->translate(glm::vec3(0, 0, -distance));
    return true;
  }
  return false;
}

bool	Player::moveLeft(double const distance)
{
  double rotate;

  rotate = (_way - LEFT) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = LEFT;
  if (_map->getTypeAt(_vec.x + distance + 1, _vec.y + _size) == GROUND &&
      _map->getTypeAt(_vec.x + distance + 1, _vec.y + 1 - _size) == GROUND) {
    _vec.x += distance;
    _obj->translate(glm::vec3(distance, 0, 0));
    return true;
  }
  return false;
}

bool	Player::moveRight(double const distance)
{
  double rotate;

  rotate = (_way - RIGHT) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = RIGHT;
  if (_map->getTypeAt(_vec.x - distance, _vec.y + _size) == GROUND &&
      _map->getTypeAt(_vec.x - distance, _vec.y + 1 - _size) == GROUND) {
    _vec.x -= distance;
    _obj->translate(glm::vec3(-distance, 0, 0));
    return true;
  }
  return false;
}

IEntity::Type Player::getType() const
{
  return IEntity::PLAYER;
}

void	Player::setStatus(Player::Status st)
{
  _status = st;
}
