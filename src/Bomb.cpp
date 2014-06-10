#include <iostream>
#include "Bomb.hpp"
#include <unistd.h>

Bomb::Bomb(APlayer *player, const glm::vec2 &pos, int range, Map *map)
  : _vec(pos), _map(map), _time(2.5), _staytime(0.25), _range(range)
{
  _obj = new GameModel(ResourceManager::getInstance()->get<Model>(RES_MODEL "bomb.fbx"));
  _player = player;
  _status = OK;
  _speed = _range * 10;

  _distance = 0;

  _obj->scale(glm::vec3(0.0025f, 0.0025f, 0.0025f));
  _obj->translate(glm::vec3(pos.x, 0, pos.y));
}

Bomb::~Bomb()
{
  delete _obj;
}

const glm::vec2	& Bomb::getPos() const
{
  return _vec;
}

void	Bomb::setPos(const glm::vec2 &new_pos)
{
  _vec = new_pos;
}

void	Bomb::update(UNUSED gdl::Input &input, gdl::Clock const &clock)
{
  _obj->scale(glm::vec3(1.0025f, 1.0025f, 1.0025f));

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
  this->spreadTop(false);
  this->spreadLeft(false);
  this->spreadDown(false);
  this->spreadRight(false);
  if (_status != DESTROY && _distance >= _range && _staytime.update(clock.getElapsed()))
    {
      _fireList.clear();
      _status = DESTROY;
      _player->setStockBomb(_player->getStockBomb() + 1);
      this->spreadTop(true);
      this->spreadLeft(true);
      this->spreadDown(true);
      this->spreadRight(true);
      SoundManager::getInstance()->manageSound(SoundManager::BOMB_EXPLOSION, SoundManager::PLAY);
      for (std::vector<ABonus *>::iterator it = _generatedBonus.begin();
           it != _generatedBonus.end(); ++it)
        {
          _map->addEntity(*it);
        }
      _generatedBonus.clear();
    }
}

char	Bomb::destroyEntity(const glm::vec2 &pos, bool destroy)
{
  IEntity *entity;

  std::vector<APlayer *> players = _map->getPlayersAt(pos.x, pos.y);
  for (std::vector<APlayer *>::iterator it = players.begin(); it != players.end(); ++it)
    {
      if ((*it)->getFlammePass() == false)
      	(*it)->setStatus(DESTROY);
    }
  entity = _map->getEntityAt(pos.x, pos.y);
  if (entity == NULL)
    return 1;
  if (entity->getType() == WALL)
    return 0;
  if (entity->getType() == BOMB && entity->getStatus() == OK)
    entity->setStatus(BURNING);
  if (entity->getType() == BOX)
    {
      if (destroy)
	{
	  if (rand() % 2)
	    _generatedBonus.push_back(BonusFactory::getInstance()->createBonus(pos, 3));
	  entity->setStatus(DESTROY);
	}
      return 2;
    }
  return 1;
}

bool	Bomb::spreadTop(bool destroy)
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);
  char ret;

  while (cpy.y < _distance + _vec.y)
    {
      if (!(ret = this->destroyEntity(cpy, destroy)))
        return false;
      fire.setPos(cpy);
      _fireList.push_back(new Fire(cpy));
      cpy.y += 1;
      if (ret == 2)
	return false;
    }
  return true;
}

bool	Bomb::spreadLeft(bool destroy)
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);
  char ret;

  while (cpy.x < _distance + _vec.x)
    {
      if (!(ret = this->destroyEntity(cpy, destroy)))
        return false;
      fire.setPos(cpy);
      _fireList.push_back(new Fire(cpy));
      cpy.x += 1;
      if (ret == 2)
	return false;
    }
  return false;
}

bool	Bomb::spreadDown(bool destroy)
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);
  char ret;

  while (cpy.y > _vec.y - _distance)
    {
      if (!(ret = this->destroyEntity(cpy, destroy)))
        return false;
      fire.setPos(cpy);
      _fireList.push_back(new Fire(cpy));
      cpy.y -= 1;
      if (ret == 2)
	return false;
    }
  return true;
}

bool	Bomb::spreadRight(bool destroy)
{
  glm::vec2 cpy = _vec;
  Fire fire(_vec);
  char ret;

  while (cpy.x > _vec.x - _distance)
    {
      if (!(ret = this->destroyEntity(cpy, destroy)))
        return false;
      fire.setPos(cpy);
      _fireList.push_back(new Fire(cpy));
      cpy.x -= 1;
      if (ret == 2)
	return false;
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
