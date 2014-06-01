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
  int y, ya;

  rotate = (_way - UP) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = UP;
  y = _vec.y + _size;
  ya = _vec.y + distance + _size;
  if (y == ya || (_map->getTypeAt(_vec.x + _size, _vec.y + distance + _size) == NONE &&
      _map->getTypeAt(_vec.x + 1 - _size, _vec.y + distance + _size) == NONE)) {
    _vec.y += distance;
    _obj->translate(glm::vec3(0, 0, distance));
    return true;
  }
  return false;
}

bool	APlayer::moveDown(double const distance)
{
  double rotate;
  int y, ya;

  rotate = (_way - DOWN) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = DOWN;
  y = _vec.y + 1 -_size;
  ya = _vec.y - distance + 1 - _size;
  if (y == ya || (_map->getTypeAt(_vec.x + _size, _vec.y - distance + 1 - _size) == NONE &&
      _map->getTypeAt(_vec.x + 1 - _size, _vec.y - distance + 1 - _size) == NONE)) {
    _vec.y -= distance;
    _obj->translate(glm::vec3(0, 0, -distance));
    return true;
  }
  return false;
}

bool	APlayer::moveLeft(double const distance)
{
  double rotate;
  int x, xa;

  rotate = (_way - LEFT) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = LEFT;
  x = _vec.x + _size;
  xa = _vec.x + distance + _size;
  if (x == xa || (_map->getTypeAt(_vec.x + distance + _size, _vec.y + _size) == NONE &&
      _map->getTypeAt(_vec.x + distance + _size, _vec.y + 1 - _size) == NONE)) {
    _vec.x += distance;
    _obj->translate(glm::vec3(distance, 0, 0));
    return true;
  }
  return false;
}

bool	APlayer::moveRight(double const distance)
{
  double rotate;
  int x, xa;

  rotate = (_way - RIGHT) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = RIGHT;
  x = _vec.x + 1 - _size;
  xa = _vec.x - distance + 1 - _size;
  if (x == xa || (_map->getTypeAt(_vec.x - distance + 1 - _size, _vec.y + _size) == NONE &&
      _map->getTypeAt(_vec.x - distance + 1 - _size, _vec.y + 1 - _size) == NONE)) {
    _vec.x -= distance;
    _obj->translate(glm::vec3(-distance, 0, 0));
    return true;
  }
  return false;
}

bool APlayer::bomb(UNUSED double const distance)
{
  int x = _vec.x + _size;
  int y = _vec.y + _size;

  _map->addEntity(new Bomb(glm::vec2(x, y), _bombList.front(), _map));
  return false;
}

IEntity::Type APlayer::getType() const
{
  return IEntity::PLAYER;
}

void	APlayer::setStatus(APlayer::Status st)
{
  _status = st;
}

IEntity::Status APlayer::getStatus() const
{
  return _statusOfObject;
}

void APlayer::setStatus(IEntity::Status status)
{
  _statusOfObject = status;
}
