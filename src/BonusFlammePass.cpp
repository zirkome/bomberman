#include "BonusFlammePass.hpp"
#include "config.h"

BonusFlammePass::BonusFlammePass(const glm::vec2 &pos, double effectTime)
  : ABonus(FLAMME_PASS, pos, effectTime)
{
}

BonusFlammePass::~BonusFlammePass()
{
}

void	BonusFlammePass::start(APlayer *player)
{
  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);

  player->setFlammePass(true);
}

void	BonusFlammePass::stop(APlayer *player)
{
  player->setFlammePass(false);
  _status = DESTROY;
}

void	BonusFlammePass::takeAnother(UNUSED APlayer *player)
{
  double	effectTime = _effectTime.getTime();

  _effectTime.addTime(effectTime);
}

std::string BonusFlammePass::toString()
{
  std::stringstream ss("");

  ss << "Bonus flamme pass "
     << " (" << static_cast<int>(_effectTime.getRemainingTime()) << ")";;
  return ss.str();
}
