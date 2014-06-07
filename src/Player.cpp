#include "config.h"
#include "Player.hpp"

Player::Player(const glm::vec2& pos, Map *map) : APlayer(pos, map)
{
  for (size_t i = 0; i < _stock; ++i) {
      _bombList.push_back(_lvl);
    }
}


Player::~Player()
{
}

void	Player::update(gdl::Input &input, gdl::Clock const &clock)
{
  double distance;
  bool	hasMoved = false;
  bool	validKey = false;

  distance = clock.getElapsed() * _speed;
  if (distance > 1.0)
    distance = 1.0;
  for (std::vector<int>::iterator it = _moveKey.begin(), end = _moveKey.end(); it != end; ++it)
    {
      if (input.getKey(*it))
        {
          hasMoved = this->movePlayer(_moveConf[*it], distance);
          validKey = true;
          break;
        }
    }
  updateAnim(hasMoved, validKey);
  for (actionPtr::iterator it = _actionPtr.begin(); it != _actionPtr.end(); ++it)
    {
      if (input.getKey(it->first))
        {
          (this->*_actionPtr[it->first])();
          return;
        }
    }
}
