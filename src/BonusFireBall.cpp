#include "BonusFireBall.hpp"

BonusFireBall::BonusFireBall(const glm::vec2 &pos, double effectTime)
: ABonus(FIREBALL, pos, effectTime)
{

}

BonusFireBall::~BonusFireBall()
{

}

void	BonusFireBall::start(APlayer *player)
{
  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);
  player->setAmmo(2);
}

void	BonusFireBall::stop(UNUSED APlayer *player)
{
  _status = DESTROY;
}

void    BonusFireBall::takeAnother(APlayer *player)
{
  double effectTime = _effectTime.getTime();

  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);
  player->setAmmo(2);
  _effectTime.reset(effectTime);
}

std::string BonusFireBall::toString()
{
  std::stringstream ss("");

  ss << "FireBall's ammo : 2";
  return ss.str();
}
