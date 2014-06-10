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
  std::cout << "flamme passe activated : " << player->getFlammePass() << std::endl;
  // _status = REMOVE;
}

void	BonusFlammePass::stop(APlayer *player)
{
  player->setFlammePass(false);
  _status = DESTROY;
  std::cout << "flamme passe ended" << std::endl;
}

void	BonusFlammePass::takeAnother(UNUSED APlayer *player)
{
  double	effectTime = _effectTime.getTime();

  _effectTime.addTime(effectTime);
}

std::string BonusFlammePass::toString()
{
  std::stringstream ss("");

  ss << "Bonus flamme pass !";
  return ss.str();
}
