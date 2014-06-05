#include "config.h"
#include "Player.hpp"

Player::Player(const glm::vec2 pos, Map *map) : APlayer(pos, map)
{
  _statusOfObject = OK;
  // _obj = AssetsManager::getInstance()->getAssets<Model>(IEntity::PLAYER);

  // Init pointer method
  _movePtr[SDLK_UP] = &Player::moveUp;
  _movePtr[SDLK_DOWN] = &Player::moveDown;
  _movePtr[SDLK_RIGHT] = &Player::moveRight;
  _movePtr[SDLK_LEFT] = &Player::moveLeft;
  _movePtr[SDLK_SPACE] = &Player::bomb;

  // Init bombList
  for (size_t i = 0; i < _stock; ++i) {
      _bombList.push_back(_lvl);
  }
}

Player::~Player()
{
}

void	Player::update(gdl::Input &input, gdl::Clock const &clock)
{
  bool	hasMoved;
  double distance;

  distance = clock.getElapsed() * _speed;
  if (distance > 1.0)
    distance = 1.0;
  for (MovePtr::const_iterator it = _movePtr.begin(), end = _movePtr.end(); it != end; ++it)
    if (input.getKey(it->first)) {
      hasMoved = (this->*_movePtr[it->first])(distance);
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
      return ;
    }
  if (_status == WALK)
    {
      _obj->setCurrentSubAnim("stop_walking", false);
      _status = STOP_WALK;
    }
}
