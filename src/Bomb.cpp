#include <iostream>
#include "Bomb.hpp"
#include <unistd.h>

Bomb::Bomb(const glm::vec2 &pos, int lvl, Map *map) :
	   _vec(pos), _lvl(lvl), _map(map), _time(2), _range(2)
{
  _status = OK;
  _speed = 4;
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
  if (_status == BURNING)
    _time.reset(0);
  if (_time.update(clock))
    this->explode(clock);
}

void	Bomb::explode(gdl::Clock const &clock)
{
  if (_status == DESTROY)
    return ;
  _status = BURNING;
  this->spreadTop(clock.getElapsed() * _speed);
  this->spreadLeft();
  this->spreadDown();
  this->spreadRight();
}

bool	Bomb::destroyEntity(int x, int y) const
{
  IEntity *entity;

  entity = _map->getEntityAt(x, y);
  if (entity && entity->getType() == WALL)
    return false;
  if (entity && entity->getType() == BOX)
    entity->setStatus(DESTROY);
  if (entity && entity->getType() == BOMB && entity->getStatus() == OK)
    entity->setStatus(BURNING);
  return true;
}

void	Bomb::spreadTop(double distance)
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);

  _distance += distance;
  if (_distance >= _range)
    _distance = _range;
  while (cpy.y <= _distance + _vec.y) {
      if (!this->destroyEntity(cpy.x, cpy.y + 1))
	return ;
      fire.setPos(cpy);
      _fireList.push_back(new Fire(cpy));
      cpy.y += 0.1;
  }
}

void	Bomb::spreadLeft()
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);

  if (_distance >= _range)
    _distance = _range;
  while (cpy.x <= _distance + _vec.x) {
      if (!this->destroyEntity(cpy.x + 1, cpy.y))
	return ;
    fire.setPos(cpy);
    _fireList.push_back(new Fire(cpy));
    cpy.x += 0.1;
  }
}

void	Bomb::spreadDown()
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);

  if (_distance >= _range)
    _distance = _range;
  while (cpy.y > _vec.y - _distance) {
    if (!this->destroyEntity(cpy.x, cpy.y))
      return ;
    fire.setPos(cpy);
    _fireList.push_back(new Fire(cpy));
    cpy.y -= 0.1;
  }
}

void	Bomb::spreadRight()
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);

  if (_distance >= _range)
    _distance = _range;
  while (cpy.x > _vec.x - _distance) {
    if (!this->destroyEntity(cpy.x, cpy.y))
      return ;
    fire.setPos(cpy);
    _fireList.push_back(new Fire(cpy));
    cpy.x -= 0.1;
  }
}

void	Bomb::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  if (_status == OK)
    _obj->draw(shader, clock);

  // draw flames
  while (_status != DESTROY && !_fireList.empty()) {
      _fireList.front()->draw(shader, clock);
      delete _fireList.front();
      _fireList.pop_front();
  }
  if (_distance >= _range)
    _status = DESTROY;
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
