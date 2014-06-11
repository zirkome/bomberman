#include "BonusRange.hpp"

BonusRange::BonusRange(const glm::vec2 &pos, double effectTime)
  : ABonus(BOMB_RANGE, pos, effectTime), _increaseRange(0)
{
}

BonusRange::~BonusRange()
{
}

void	BonusRange::start(APlayer *player)
{
  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);

  _oldRange = player->getBombRange();
  _increaseRange += 1;

  player->setBombRange(_oldRange + 1);
}

void	BonusRange::stop(UNUSED APlayer *player)
{
  _status = DESTROY;
}

void	BonusRange::takeAnother(APlayer *player)
{
  double	effectTime = _effectTime.getTime();
  double	oldRange = player->getBombRange();

  player->setBombRange(oldRange + 1);
  _effectTime.addTime(effectTime);
}

std::string BonusRange::toString()
{
  std::stringstream ss("");

  ss << "Bomb range increase to " << _increaseRange + _oldRange;
  return ss.str();
}
