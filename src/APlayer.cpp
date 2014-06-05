#include "APlayer.hpp"
# include "Bomb.hpp"

APlayer::APlayer(const glm::vec2 &pos, Map *map) : _vec(pos), _map(map), _time(2)
{
  _stock = 1;

  _obj = new Model(RES_MODEL "marvin.fbx");

  _obj->translate(glm::vec3(pos.x, -0.5, pos.y));
  _obj->scale(glm::vec3(0.0025, 0.0025, 0.0025));

  _status = STANDBY;
  _speed = 4;
  _way = UP;
  _size = 0.7;
  _lvl = 1;

  _obj->createSubAnim(0, "standby", 0, 0);
  _obj->createSubAnim(0, "walk", 13, 63);
  _obj->createSubAnim(0, "stop_walking", 64, 140);
  _obj->setCurrentSubAnim("standby");
}

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
  bool hasMoved = false;

  rotate = (_way - UP) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = UP;
  y = _vec.y + _size;
  ya = _vec.y + distance + _size;
  if (y == ya || (_map->getTypeAt(_vec.x + _size, _vec.y + distance + _size) == NONE &&
      _map->getTypeAt(_vec.x + 1 - _size, _vec.y + distance + _size) == NONE)) {
    _vec.y += distance;
    _obj->translate(glm::vec3(0, 0, distance));
    hasMoved = true;
  }
  updateAnim(hasMoved);
  return hasMoved;
}

bool	APlayer::moveDown(double const distance)
{
  double rotate;
  int y, ya;
  bool hasMoved = false;

  rotate = (_way - DOWN) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = DOWN;
  y = _vec.y + 1 -_size;
  ya = _vec.y - distance + 1 - _size;
  if (y == ya || (_map->getTypeAt(_vec.x + _size, _vec.y - distance + 1 - _size) == NONE &&
      _map->getTypeAt(_vec.x + 1 - _size, _vec.y - distance + 1 - _size) == NONE)) {
    _vec.y -= distance;
    _obj->translate(glm::vec3(0, 0, -distance));
    hasMoved = true;
  }
  updateAnim(hasMoved);
  return hasMoved;
}

bool	APlayer::moveLeft(double const distance)
{
  double rotate;
  int x, xa;
  bool hasMoved = false;

  rotate = (_way - LEFT) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = LEFT;
  x = _vec.x + _size;
  xa = _vec.x + distance + _size;
  if (x == xa || (_map->getTypeAt(_vec.x + distance + _size, _vec.y + _size) == NONE &&
      _map->getTypeAt(_vec.x + distance + _size, _vec.y + 1 - _size) == NONE)) {
    _vec.x += distance;
    _obj->translate(glm::vec3(distance, 0, 0));
    hasMoved = true;
  }
  updateAnim(hasMoved);
  return hasMoved;
}

bool	APlayer::moveRight(double const distance)
{
  double rotate;
  int x, xa;
  bool hasMoved = false;

  rotate = (_way - RIGHT) * 90;
  _obj->rotate(glm::vec3(0, 1, 0), rotate);
  _way = RIGHT;
  x = _vec.x + 1 - _size;
  xa = _vec.x - distance + 1 - _size;
  if (x == xa || (_map->getTypeAt(_vec.x - distance + 1 - _size, _vec.y + _size) == NONE &&
      _map->getTypeAt(_vec.x - distance + 1 - _size, _vec.y + 1 - _size) == NONE)) {
    _vec.x -= distance;
    _obj->translate(glm::vec3(-distance, 0, 0));
    hasMoved = true;
  }
  updateAnim(hasMoved);
  return hasMoved;
}

void	APlayer::updateAnim(bool hasMoved)
{
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
}

void APlayer::createBomb()
{
  _bombList.push_back(_lvl);
}

bool APlayer::bomb(UNUSED double const distance)
{
  int x = _vec.x + _size;
  int y = _vec.y + _size;
  static int prevX = 0;
  static int prevY = 0;

  if (prevX == x && prevY == y)
    return false;
  if (!_bombList.empty()) {
      _map->addEntity(new Bomb(this, glm::vec2(x, y), _bombList.front(), _map));
      _bombList.pop_front();
      prevX = x;
      prevY = y;
  }
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
