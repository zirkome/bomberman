#include "BonusWalk.hpp"

BonusWalk::BonusWalk(BonusType typeWalk, glm::vec2 pos, double effectTime)
  : ABonus(typeWalk, pos, effectTime), _typeWalk(typeWalk)
{
}

BonusWalk::~BonusWalk()
{

}

void	BonusWalk::start(APlayer *player)
{
  double currentSpeed = player->getSpeed();

  if (_typeWalk == FASTER)
    {
      std::cout << "speed up !" << std::endl;
      _increaseSpeed = (currentSpeed * 1.3) - currentSpeed;
    }
  else
    {
      std::cout << "speed down !" << std::endl;
      _increaseSpeed = -(currentSpeed - (currentSpeed * 0.7));
    }
  std::cout << "speed now at : " << currentSpeed + _increaseSpeed << std::endl;
  player->setSpeed(currentSpeed + _increaseSpeed);
  _status = REMOVE;
}

void	BonusWalk::update(APlayer *player, const gdl::Clock &clock)
{
  if (_effectTime.update(clock.getElapsed()))
    {
      stop(player);
    }
}

void	BonusWalk::stop(APlayer *player)
{
  double currentSpeed = player->getSpeed();

  _status = DESTROY;
  player->setSpeed(currentSpeed - _increaseSpeed);
  std::cout << "bonusWalk end : " << player->getSpeed() << std::endl;
}

std::string BonusWalk::toString()
{
  std::stringstream ss("");

  ss << (_typeWalk == FASTER ? "Faster : " : "Slowly : -") << _increaseSpeed;
  return ss.str();
}
