#include "APlayer.hpp"
# include "Bomb.hpp"

APlayer::APlayer(const glm::vec2 &pos, Map *map)
  : _pos(pos), _map(map), _time(2)
{
  _stock = 1;

  _obj = new GameModel(RES_MODEL "marvin.fbx");
  _obj->translate(glm::vec3(pos.x, -0.5, pos.y));
  _obj->scale(glm::vec3(0.0025, 0.0025, 0.0025));

  _statusOfObject = OK;
  _status = STANDBY;
  _speed = 3;
  _way = UP;
  _size = 0.7;
  _lvl = 1;

  (*_obj)->createSubAnim(0, "standby", 0, 0);
  (*_obj)->createSubAnim(0, "walk", 0, 30);
  (*_obj)->createSubAnim(0, "stop_walking", 30, 60);
  (*_obj)->setCurrentSubAnim("standby");
}

APlayer::~APlayer()
{
  delete _obj;
  for (std::map<int, movementCoef*>::iterator it = _moveConf.begin();
       it != _moveConf.end(); ++it)
    {
      delete it->second;
    }
}

const glm::vec2	&APlayer::getPos() const
{
  return _pos;
}

void	APlayer::setPos(const glm::vec2 &new_pos)
{
  _pos = new_pos;
}

void	APlayer::draw(gdl::AShader *shader, const gdl::Clock& clock) const
{
  _obj->draw(shader, clock);
}

bool	APlayer::movePlayer(const movementCoef *mcoef, float const distance)
{
  glm::vec2	toGoLeft;
  glm::vec2	toGoRight;
  bool	hasMoved = false;

  // reset rotation
  _obj->setRotation(glm::vec3(0, 0, 0));
  _obj->rotate(glm::vec3(0, 1, 0), mcoef->rotate);

  // get point to go left end right in front the player
  toGoLeft = _pos + (mcoef->dir * distance) + mcoef->distLeft;
  toGoRight = _pos + (mcoef->dir * distance) + mcoef->distRight;

  // if the points to go are on the same piece of field or
  // if the type to go is free --> move

  if ((glm::ivec2(toGoLeft) == glm::ivec2(_pos + mcoef->distLeft) &&
       glm::ivec2(toGoRight) == glm::ivec2(_pos + mcoef->distRight)) ||
      (_map->getTypeAt(toGoLeft.x, toGoLeft.y) == NONE &&
       _map->getTypeAt(toGoRight.x, toGoRight.y) == NONE))
    {
      _pos += mcoef->dir * distance;
      _obj->translate(mcoef->translate * distance);
      hasMoved = true;
    }
  return hasMoved;
}

void	APlayer::updateAnim(bool hasMoved, bool keyPressed)
{
  if (keyPressed == false)
    {
      if (_status == WALK)
        {
          (*_obj)->setCurrentSubAnim("stop_walking", false);
          _status = STOP_WALK;
        }
      return;
    }
  if (_status != WALK && hasMoved)
    {
      _status = WALK;
      (*_obj)->setCurrentSubAnim("walk");
    }
  else if (_status == WALK && !hasMoved)
    {
      (*_obj)->setCurrentSubAnim("stop_walking", false);
      _status = STOP_WALK;
    }
}

void APlayer::createBomb()
{
  _bombList.push_back(_lvl);
}

bool APlayer::bomb()
{
  int x = _pos.x + _size;
  int y = _pos.y + _size;

  if (_map->getTypeAt(x, y) != NONE)
    return false;
  if (!_bombList.empty()) {
      _map->addEntity(new Bomb(this, glm::vec2(x, y), _bombList.front(), _map));
      _bombList.pop_front();
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
