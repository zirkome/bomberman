#include "APlayer.hpp"

APlayer::~APlayer()
{
}

const glm::vec2	&APlayer::getPos() const
{
  return _vec;
}

void	APlayer::setPos(const glm::vec2 &new_pos)
{
  _vec = new_pos;
}

void	APlayer::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  _obj->draw(shader, clock);
}

bool	APlayer::moveUp(double const distance)
{
  double rotate;

  rotate = (_way - UP) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = UP;
  if (_map->getTypeAt(_vec.x + _size, _vec.y + distance + _size) == NONE &&
      _map->getTypeAt(_vec.x + 1 - _size, _vec.y + distance + _size) == NONE) {
    _vec.y += distance;
    _obj->translate(glm::vec3(0, 0, distance));
    return true;
  }
  return false;
}

bool	APlayer::moveDown(double const distance)
{
  double rotate;

  rotate = (_way - DOWN) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = DOWN;
  if (_map->getTypeAt(_vec.x + _size, _vec.y - distance + 1 - _size) == NONE &&
      _map->getTypeAt(_vec.x + 1 - _size, _vec.y - distance + 1 - _size) == NONE) {
    _vec.y -= distance;
    _obj->translate(glm::vec3(0, 0, -distance));
    return true;
  }
  return false;
}

bool	APlayer::moveLeft(double const distance)
{
  double rotate;

  rotate = (_way - LEFT) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = LEFT;
  if (_map->getTypeAt(_vec.x + distance + _size, _vec.y + _size) == NONE &&
      _map->getTypeAt(_vec.x + distance + _size, _vec.y + 1 - _size) == NONE) {
    _vec.x += distance;
    _obj->translate(glm::vec3(distance, 0, 0));
    return true;
  }
  return false;
}

bool	APlayer::moveRight(double const distance)
{
  double rotate;

  rotate = (_way - RIGHT) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = RIGHT;
  if (_map->getTypeAt(_vec.x - distance + 1 - _size, _vec.y + _size) == NONE &&
      _map->getTypeAt(_vec.x - distance + 1 - _size, _vec.y + 1 - _size) == NONE) {
    _vec.x -= distance;
    _obj->translate(glm::vec3(-distance, 0, 0));
    return true;
  }
  return false;
}

bool APlayer::bomb(UNUSED double const distance)
{
  return true;
}

IEntity::Type APlayer::getType() const
{
  return IEntity::PLAYER;
}

void	APlayer::setStatus(APlayer::Status st)
{
  _status = st;
}
