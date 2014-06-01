#include "config.h"
#include "Player.hpp"

Player::Player(const glm::vec2 pos, Map *map)
{
  _statusOfObject = OK;
  // _obj = AssetsManager::getInstance()->getAssets<Model>(IEntity::PLAYER);
  _obj = new Model(RES_MODEL "marvin.fbx");

  _obj->translate(glm::vec3(pos.x, -0.5, pos.y));
  _obj->scale(glm::vec3(0.0025, 0.0025, 0.0025));

  // Init pointer method
  _movePtr[SDLK_UP] = &Player::moveUp;
  _movePtr[SDLK_DOWN] = &Player::moveDown;
  _movePtr[SDLK_RIGHT] = &Player::moveRight;
  _movePtr[SDLK_LEFT] = &Player::moveLeft;
  _movePtr[SDLK_SPACE] = &Player::bomb;

  _status = STANDBY;
  _vec = pos;
  _map = map;
  _speed = 4;
  _way = UP;
  _size = 0.7;

  _obj->createSubAnim(0, "standby", 0, 0);
  _obj->createSubAnim(0, "walk", 42, 63);
  _obj->createSubAnim(0, "stop_walking", 64, 121);
  _obj->setCurrentSubAnim("standby");

  // Init bombList
  _bombList.push_back(1);
}

Player::~Player()
{
}

void	Player::update(gdl::Input &input, gdl::Clock const &clock)
{
  bool	hasMoved;

  for (MovePtr::const_iterator it = _movePtr.begin(), end = _movePtr.end(); it != end; ++it)
    if (input.getKey(it->first)) {
      hasMoved = (this->*_movePtr[it->first])(clock.getElapsed() * _speed);
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
