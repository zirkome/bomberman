#include "BonusFireBall.hpp"
#include "config.h"

BonusFireBall::BonusFireBall(const glm::vec2 &pos, const movementCoef *mcoef, Map *map,
    APlayer *player)
: _pos(pos), _mcoef(mcoef), _map(map), _speed(4), _player(player)
{
  _status = OK;
  _obj = new GameGeometry(ResourceManager::getInstance()->get<AGeometry>("cube.geo"));
  _texture = ResourceManager::getInstance()->get<Texture>(RES_TEXTURE "bonus_fireball.tga");

  _obj->scale(glm::vec3(0.2f, 0.005f, 0.2f));
  _obj->translate(glm::vec3(pos.x, 0, pos.y));
  _obj->rotate(glm::vec3(0, 1, 0), 90);
  _obj->rotate(glm::vec3(0, 1, 0), _mcoef->rotate);

  glm::vec2 toGoLeft = _pos + (_mcoef->dir * 1.0f) + _mcoef->distLeft;
  glm::vec2 toGoRight = _pos + (_mcoef->dir * 1.0f) + _mcoef->distRight;

  IEntity *left = _map->getEntityAt(toGoLeft.x, toGoLeft.y);
  IEntity *right = _map->getEntityAt(toGoRight.x, toGoRight.y);

  if ((!left && !right)) {
      _pos += _mcoef->dir * 1.0f;
      _obj->translate(_mcoef->translate * 1.0f);
  }
}

BonusFireBall::~BonusFireBall()
{
  delete _obj;
}

const glm::vec2	&BonusFireBall::getPos() const
{
  return _pos;
}

void	BonusFireBall::setPos(const glm::vec2 &newPos)
{
  _obj->translate(glm::vec3(newPos.x - _pos.x, 0, newPos.y - _pos.y));
  _pos = newPos;
}

void	BonusFireBall::update(UNUSED gdl::Input &input, gdl::Clock const &clock)
{
  float distance = clock.getElapsed() * _speed;
  glm::vec2 toGoLeft = _pos + (_mcoef->dir * distance) + _mcoef->distLeft;
  glm::vec2 toGoRight = _pos + (_mcoef->dir * distance) + _mcoef->distRight;

  std::vector<APlayer *> playersLeft = _map->getPlayersAt(toGoLeft.x, toGoLeft.y);
  std::vector<APlayer *> playersRight = _map->getPlayersAt(toGoLeft.x, toGoLeft.y);

  IEntity *left = _map->getEntityAt(toGoLeft.x, toGoLeft.y);
  IEntity *right = _map->getEntityAt(toGoRight.x, toGoRight.y);

  if (!playersLeft.empty())
    left = *(playersLeft.begin());
  if (!playersRight.empty())
      right = *(playersRight.begin());

  if ((!left && !right) || (left->getType() == BONUS && right->getType() == BONUS)) {
      _pos += _mcoef->dir * distance;
      _obj->translate(_mcoef->translate * distance);
  }
  else {
    _status = DESTROY;
    if (left)
      destroyEntity(left);
    if (right)
      destroyEntity(left);
  }
}

void	BonusFireBall::draw(gdl::AShader *shader, const gdl::Clock& clock) const
{
  _texture->bind();
  _obj->draw(shader, clock);
}

void	BonusFireBall::destroyEntity(IEntity *entity)
{
  if (entity->getType() == BOMB && entity->getStatus() == OK)
    entity->setStatus(BURNING);
  if (entity->getType() == BOX)
    {
      if (rand() % 2)
	_map->addEntity(BonusFactory::getInstance()->createBonus(entity->getPos()));
      entity->setStatus(DESTROY);
      _player->increaseScores(1);
    }
  if (entity->getType() == PLAYER) {
      entity->setStatus(DESTROY);
      _player->increaseScores(10);
  }
}

IEntity::Type BonusFireBall::getType() const
{
  return IEntity::FIREBALL;
}

IEntity::Status BonusFireBall::getStatus() const
{
  return _status;
}

void BonusFireBall::setStatus(IEntity::Status status)
{
  _status = status;
}
