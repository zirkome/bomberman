#include "APlayer.hpp"
# include "Bomb.hpp"

APlayer::APlayer(const glm::vec2 &pos, Map *map)
  : _pos(pos), _map(map)
{
  _stock = 1;

  _obj = new Model(RES_MODEL "marvin.fbx");

  _obj->translate(glm::vec3(pos.x, -0.5, pos.y));
  _obj->scale(glm::vec3(0.0025, 0.0025, 0.0025));

  _statusOfObject = OK;
  _status = STANDBY;
  _speed = 3;
  _way = UP;
  _size = 0.7;
  _lvl = 1;

  _obj->createSubAnim(0, "standby", 0, 0);
  _obj->createSubAnim(0, "walk", 0, 30);
  _obj->createSubAnim(0, "stop_walking", 30, 60);
  _obj->setCurrentSubAnim("standby");

  _moveKey.push_back(SDLK_UP);
  _moveKey.push_back(SDLK_DOWN);
  _moveKey.push_back(SDLK_LEFT);
  _moveKey.push_back(SDLK_RIGHT);

  _actionPtr[SDLK_SPACE] = &APlayer::bomb;

  _moveConf[SDLK_UP] = new movementCoef(0, glm::vec2(0.0, 1.0),
                                        glm::vec3(0, 0, 1),
                                        glm::vec2(0.7, 0.7),
                                        glm::vec2(0.2, 0.7));

  _moveConf[SDLK_DOWN] = new movementCoef(180, glm::vec2(0.0, -1.0),
                                          glm::vec3(0, 0, -1),
                                          glm::vec2(0.7, 0.2),
                                          glm::vec2(0.2, 0.2));

  _moveConf[SDLK_RIGHT] = new movementCoef(-90, glm::vec2(-1.0, 0.0),
      glm::vec3(-1, 0, 0),
      glm::vec2(0.2, 0.7),
      glm::vec2(0.2, 0.2));

  _moveConf[SDLK_LEFT] = new movementCoef(90, glm::vec2(1.0, 0.0),
                                          glm::vec3(1, 0, 0),
                                          glm::vec2(0.7, 0.7),
                                          glm::vec2(0.7, 0.2));
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
  bool	isBonus = false;

  // reset rotation
  _obj->setRotation(glm::vec3(0, 0, 0));
  _obj->rotate(glm::vec3(0, 1, 0), mcoef->rotate);

  // get point to go left end right in front the player
  toGoLeft = _pos + (mcoef->dir * distance) + mcoef->distLeft;
  toGoRight = _pos + (mcoef->dir * distance) + mcoef->distRight;

  // if the points to go are on the same piece of field or
  // if the type to go is free --> move

  if ((glm::ivec2(toGoLeft) == glm::ivec2(_pos + mcoef->distLeft) &&
       glm::ivec2(toGoRight) == glm::ivec2(_pos + mcoef->distRight)))
    {
      _pos += mcoef->dir * distance;
      _obj->translate(mcoef->translate * distance);
      return true;
    }
  IEntity *left = _map->getEntityAt(toGoLeft.x, toGoLeft.y);
  IEntity *right = _map->getEntityAt(toGoRight.x, toGoRight.y);

  if (left && left->getType() == IEntity::BONUS && left->getStatus() != IEntity::REMOVE)
    {
      // std::cout << "i take left" << std::endl;
      ABonus *bonus = static_cast<ABonus *>(left);

      bonus->start(this);
      _bonus.push_back(bonus);
      hasMoved = true;
      isBonus = true;
    }
  if (right && right->getType() == IEntity::BONUS && right->getStatus() != IEntity::REMOVE)
    {
      // std::cout << "i take right" << std::endl;
      ABonus *bonus = static_cast<ABonus *>(right);

      bonus->start(this);
      _bonus.push_back(bonus);
      hasMoved = true;
      isBonus = true;
    }
  if ((!left && !right) || isBonus)
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
          _obj->setCurrentSubAnim("stop_walking", false);
          _status = STOP_WALK;
        }
      return;
    }
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

void	APlayer::updateBonus(const gdl::Clock &clock)
{
  for (std::vector<ABonus *>::iterator it = _bonus.begin(), end = _bonus.end(); it != end; it++)
    {
      (*it)->update(this, clock);
      if ((*it)->getStatus() == IEntity::DESTROY)
	{
	  delete (*it);
	  _bonus.erase(it);
	}
    }
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

double APlayer::getSpeed() const
{
  return _speed;
}

void	APlayer::setSpeed(double speed)
{
  _speed = speed;
}
