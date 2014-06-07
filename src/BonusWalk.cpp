#include "BonusWalk.hpp"

BonusWalk::BonusWalk(BonusType typeWalk, glm::vec2 pos, double effectTime)
  : ABonus(typeWalk, pos, effectTime), _taken(false), _typeWalk(typeWalk)
{
}

BonusWalk::~BonusWalk()
{

}

void	BonusWalk::start(APlayer *player)
{
  double currentSpeed = player->getSpeed();

  if (_typeWalk == FASTER)
    _increaseSpeed = 10;
  else
    _increaseSpeed = ((currentSpeed - 10) <= 0 ? 0 : -10);

  player->setSpeed(currentSpeed + _increaseSpeed);
  _taken = true;
  _status = REMOVE;
}

void	BonusWalk::update(APlayer *player, const gdl::Clock &clock)
{
  if (_taken == false && _toDisplay.update(clock.getElapsed()))
    {
      _status = DESTROY;
    }
  if (_taken == true && _effectTime.update(clock.getElapsed()))
    {
      stop(player);
    }
}

void	BonusWalk::stop(APlayer *player)
{
  double currentSpeed = player->getSpeed();

  player->setSpeed(currentSpeed + _increaseSpeed);
}

std::string BonusWalk::toString()
{
  std::stringstream ss("");

  ss << (_typeWalk == FASTER ? "Faster : " : "Slowly : -") << _increaseSpeed;
  return ss.str();
}
