#include "APlayer.hpp"
# include "Bomb.hpp"

APlayer::APlayer(const glm::vec2 &pos, Map *map, const glm::vec4& color)
  : _pos(pos), _map(map), _flammePass(false), _bombPass(false), _color(color)
{
  _max_bomb = 1;

  _stock_bomb = _max_bomb;
  _bomb_range = 2;

  _obj = new GameModel(RES_MODEL "marvin.fbx");
  _obj->translate(glm::vec3(pos.x, -0.5, pos.y));
  _obj->scale(glm::vec3(0.0025, 0.0025, 0.0025));

  _colorTexture = ResourceManager::getInstance()->get<Texture>(RES_TEXTURE "marvin_color.tga");
  _defaultColorTexture = ResourceManager::getInstance()->get<Texture>(RES_TEXTURE "dcolor.tga");

  _statusOfObject = OK;
  _status = STANDBY;
  _speed = 4;
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
  glActiveTexture(GL_TEXTURE1);
  _colorTexture->bind();
  shader->setUniform("fTexture1", 1);
  shader->setUniform("gColor", _color);
  glActiveTexture(GL_TEXTURE0);
  _obj->draw(shader, clock);
  glActiveTexture(GL_TEXTURE1);
  _defaultColorTexture->bind();
  shader->setUniform("gColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  glActiveTexture(GL_TEXTURE0);
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

  if (left && left->getType() == IEntity::BONUS
      && left->getStatus() != IEntity::REMOVE
      && left->getStatus() != IEntity::DESTROY)
    {
      ABonus *bonus = static_cast<ABonus *>(left);

      addBonus(bonus);
      // bonus->start(this);
      // _bonus.push_back(bonus);
      hasMoved = true;
      isBonus = true;
    }
  if (right && right->getType() == IEntity::BONUS
      && right->getStatus() != IEntity::REMOVE
      && right->getStatus() != IEntity::DESTROY)
    {
      ABonus *bonus = static_cast<ABonus *>(right);

      addBonus(bonus);
      // bonus->start(this);
      // _bonus.push_back(bonus);
      hasMoved = true;
      isBonus = true;
    }

  // check if _bompass activated
  if ((!left && !right) || isBonus ||
      ((!left || (left->getType() == IEntity::BOMB)) &&
       (!right || (right->getType() == IEntity::BOMB)) && _bombPass))
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

bool APlayer::bomb()
{
  int x = _pos.x + _size;
  int y = _pos.y + _size;

  if (_map->getTypeAt(x, y) != NONE)
    return false;
  if (_stock_bomb > 0)
    {
      _map->addEntity(new Bomb(this, glm::vec2(x, y), _bomb_range, _map));
      _stock_bomb--;
    }
  return false;
}

void	APlayer::updateBonus(const gdl::Clock &clock)
{
  for (std::vector<ABonus *>::iterator it = _bonus.begin(); it != _bonus.end(); ++it)
    {
      (*it)->update(this, clock);
      if ((*it)->getStatus() == IEntity::DESTROY)
        {
          delete (*it);
          _bonus.erase(it--);
        }
    }
}

void	APlayer::addBonus(ABonus *bonus)
{
  for (std::vector<ABonus *>::iterator it = _bonus.begin();
       it != _bonus.end(); ++it)
    {
      if (*bonus == *(*it) && (*it)->getStatus() != IEntity::DESTROY)
	{
	  (*it)->takeAnother(this);
	  bonus->setStatus(IEntity::DESTROY);
	  return;
	}
    }
  bonus->start(this);
  bonus->setStatus(IEntity::REMOVE);
  _bonus.push_back(bonus);
}

const std::vector<ABonus *>& APlayer::getBonus() const
{
  return _bonus;
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

int APlayer::getStockBomb() const
{
  return _stock_bomb;
}

void	APlayer::setStockBomb(int nbBomb)
{
  if (nbBomb <= _max_bomb)
    _stock_bomb = nbBomb;
}

int APlayer::getMaxBomb() const
{
  return _max_bomb;
}

void	APlayer::setMaxBomb(int maxBomb)
{
  _max_bomb = maxBomb;
}

double APlayer::getBombRange() const
{
  return _bomb_range;
}

void	APlayer::setBombRange(double newRange)
{
  _bomb_range = newRange;
}

void	APlayer::setBombPass(bool val)
{
  _bombPass = val;
}

bool	APlayer::getBombPass() const
{
  return _bombPass;
}

void	APlayer::setFlammePass(bool val)
{
  _flammePass = val;
}

bool	APlayer::getFlammePass() const
{
  return _flammePass;
}
