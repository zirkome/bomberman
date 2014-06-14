#include "config.h"
#include "Player.hpp"

Player::Player(const glm::vec2& pos, Map *map, bool first, const glm::vec4& color, const std::string &name)
  : APlayer::APlayer(pos, map, color, name)
{
  if (first) {
      _moveKey.push_back(SDLK_z);
      _moveKey.push_back(SDLK_s);
      _moveKey.push_back(SDLK_d);
      _moveKey.push_back(SDLK_q);
      _actionPtr[SDLK_TAB] = &Player::bomb;
      _actionPtr[SDLK_a] = &Player::fireBall;
    }
  else {
      _moveKey.push_back(SDLK_UP);
      _moveKey.push_back(SDLK_DOWN);
      _moveKey.push_back(SDLK_RIGHT);
      _moveKey.push_back(SDLK_LEFT);
      _actionPtr[SDLK_SPACE] = &Player::bomb;
      _actionPtr[SDLK_m] = &Player::fireBall;
    }

  std::vector<int>::const_iterator it = _moveKey.begin();

  _moveConf[*it++] = new movementCoef(0, glm::vec2(0.0, 1.0),
                                      glm::vec3(0, 0, 1),
                                      glm::vec2(0.7, 0.7),
                                      glm::vec2(0.2, 0.7));

  _moveConf[*it++] = new movementCoef(180, glm::vec2(0.0, -1.0),
                                      glm::vec3(0, 0, -1),
                                      glm::vec2(0.7, 0.2),
                                      glm::vec2(0.2, 0.2));

  _moveConf[*it++] = new movementCoef(-90, glm::vec2(-1.0, 0.0),
                                      glm::vec3(-1, 0, 0),
                                      glm::vec2(0.2, 0.7),
                                      glm::vec2(0.2, 0.2));

  _moveConf[*it++] = new movementCoef(90, glm::vec2(1.0, 0.0),
                                      glm::vec3(1, 0, 0),
                                      glm::vec2(0.7, 0.7),
                                      glm::vec2(0.7, 0.2));
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
  updateBonus(clock);
  _reload.update(clock.getElapsed());

  for (std::vector<int>::iterator it = _moveKey.begin(); it != _moveKey.end(); ++it)
    {
      if (input.getKey(*it))
        {
          hasMoved = this->movePlayer(_moveConf[*it], distance);
          validKey = true;
          _mcoef = _moveConf[*it];
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
