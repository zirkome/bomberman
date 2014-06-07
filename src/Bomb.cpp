#include <iostream>
#include "Bomb.hpp"
#include <unistd.h>

Bomb::Bomb(APlayer *player, const glm::vec2 &pos, int lvl, Map *map) :
  _vec(pos), _lvl(lvl), _map(map), _time(2), _staytime(0.25), _range(2 + lvl)
{
  _player = player;
  _status = OK;
  _speed = _range * 10;
  _distance = 0;
  _obj = new Model(RES_MODEL "bomb.fbx");
  _obj->scale(glm::vec3(0.0025f, 0.0025f, 0.0025f));
  _obj->translate(glm::vec3(pos.x, 0, pos.y));
}

Bomb::~Bomb()
{

}

const glm::vec2	&Bomb::getPos() const
{
  return _vec;
}

void	Bomb::setPos(const glm::vec2 &new_pos)
{
  _vec = new_pos;
}

void	Bomb::update(UNUSED gdl::Input &input, gdl::Clock const &clock)
{
  _obj->scale(glm::vec3(1.005f, 1.005f, 1.005f));
  if (_status == BURNING || _time.update(clock.getElapsed()))
    {
      this->explode(clock);
    }
}

void	Bomb::explode(gdl::Clock const &clock)
{
  if (_status == DESTROY)
    return ;
  _status = BURNING;
  _distance += clock.getElapsed() * _speed;
  if (_distance >= _range)
    _distance = _range;
  this->spreadTop();
  this->spreadLeft();
  this->spreadDown();
  this->spreadRight();
  if (_status != DESTROY && _distance >= _range && _staytime.update(clock.getElapsed()))
    {
      _fireList.clear();
      _status = DESTROY;
      _player->createBomb();
      SoundManager::getInstance()->manageSound(SoundManager::BOMB_EXPLOSION, SoundManager::PLAY);
    }
}

bool	Bomb::destroyEntity(int x, int y) const
{
  IEntity *entity;

  entity = _map->getEntityAt(x, y);
  if (!entity || entity == this)
    entity = _map->getPlayerAt(x, y);
  if (!entity)
    return true;
  if (entity->getType() == WALL)
    return false;
  if (entity->getType() != BOMB)
    entity->setStatus(DESTROY);
  if (entity->getType() == BOMB && entity->getStatus() == OK)
    entity->setStatus(BURNING);
  if (entity->getType() == BOX)
    return false;
  return true;
}

bool	Bomb::spreadTop()
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);

  while (cpy.y < _distance + _vec.y) {
      if (!this->destroyEntity(cpy.x, cpy.y))
        return false;
      fire.setPos(cpy);
      _fireList.push_back(new Fire(cpy));
      cpy.y += 1;
    }
  return true;
}

bool	Bomb::spreadLeft()
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);

  while (cpy.x < _distance + _vec.x) {
      if (!this->destroyEntity(cpy.x, cpy.y))
        return true;
      fire.setPos(cpy);
      _fireList.push_back(new Fire(cpy));
      cpy.x += 1;
    }
  return false;
}

bool	Bomb::spreadDown()
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);

  while (cpy.y > _vec.y - _distance) {
      if (!this->destroyEntity(cpy.x, cpy.y))
        return false;
      fire.setPos(cpy);
      _fireList.push_back(new Fire(cpy));
      cpy.y -= 1;
    }
  return true;
}

bool	Bomb::spreadRight()
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);

  while (cpy.x > _vec.x - _distance) {
      if (!this->destroyEntity(cpy.x, cpy.y))
        return false;
      fire.setPos(cpy);
      _fireList.push_back(new Fire(cpy));
      cpy.x -= 1;
    }
  return true;
}

void	Bomb::draw(gdl::AShader *shader, const gdl::Clock& clock) const
{
  if (_status == OK)
    _obj->draw(shader, clock);

  // draw flames
  for (FireList::const_iterator it = _fireList.begin(), end = _fireList.end();
       it != end; ++it)
    if (_status == BURNING)
      (*it)->draw(shader, clock);
}

IEntity::Type Bomb::getType() const
{
  return IEntity::BOMB;
}

IEntity::Status Bomb::getStatus() const
{
  return _status;
}

void Bomb::setStatus(IEntity::Status status)
{
  _status = status;
}
