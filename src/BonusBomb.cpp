#include "BonusBomb.hpp"

BonusBomb::BonusBomb(const glm::vec2 &pos, double effectTime)
  : ABonus(MULTI_BOMB, pos, effectTime), _increaseBomb(0)
{
  _oldStockBomb = 0;
  _oldMaxBomb = 0;
}

BonusBomb::~BonusBomb()
{
}

void	BonusBomb::start(APlayer *player)
{
  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);
  _oldStockBomb = player->getStockBomb();
  _oldMaxBomb = player->getMaxBomb();

  _increaseBomb += 1;

  player->setMaxBomb(_oldMaxBomb + _increaseBomb);
  player->setStockBomb(_oldMaxBomb + _increaseBomb);
}

void	BonusBomb::stop(APlayer *player)
{
  double curMaxBomb = player->getMaxBomb();

  _status = DESTROY;
  player->setMaxBomb(curMaxBomb - _increaseBomb);

  std::cout << "bonusBomb end : " << player->getStockBomb() << std::endl;
}

void    BonusBomb::takeAnother(APlayer *player)
{
  double	effectTime = _effectTime.getTime();
  int oldMaxBomb = player->getMaxBomb();

  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);

  _increaseBomb += 1;

  player->setMaxBomb(oldMaxBomb + 1);
  player->setStockBomb(oldMaxBomb + 1);

  _effectTime.reset(effectTime);
}

std::string BonusBomb::toString()
{
  std::stringstream ss("");

  ss << "Stock Bomb increase : " << _increaseBomb;
  return ss.str();
}
