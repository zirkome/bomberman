#include "BonusBombPass.hpp"
#include "config.h"

BonusBombPass::BonusBombPass(const glm::vec2 &pos, double effectTime)
  : ABonus(BOMB_PASS, pos, effectTime)
{
}

BonusBombPass::~BonusBombPass()
{
}

void	BonusBombPass::start(APlayer *player)
{
  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);

  player->setBombPass(true);
  // _status = REMOVE;
}

void	BonusBombPass::stop(APlayer *player)
{
  player->setBombPass(false);
  _status = DESTROY;

}

void	BonusBombPass::takeAnother(UNUSED APlayer *player)
{
  double	effectTime = _effectTime.getTime();

  _effectTime.reset(effectTime);
}

std::string BonusBombPass::toString()
{
  std::stringstream ss("");

  ss << "Bomb pass"
     << " (" << static_cast<int>(_effectTime.getRemainingTime()) << ")";
  return ss.str();
}
