#include "BonusBomb.hpp"

BonusBomb::BonusBomb(const glm::vec2 &pos, double effectTime)
  : ABonus(MULTI_BOMB, pos, effectTime)
{
}

BonusBomb::~BonusBomb()
{
}

void	BonusBomb::start(APlayer *player)
{
  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);
  _oldStockBomb = player->getStockBomb();
  _oldMaxBomb = player->getMaxBomb();

  _increaseBomb = 3;

  player->setMaxBomb(_oldMaxBomb + _increaseBomb);
  player->setStockBomb(_oldMaxBomb + _increaseBomb);

  _status = REMOVE;
}

void	BonusBomb::stop(APlayer *player)
{
  double        curMaxBomb = player->getMaxBomb();

  _status = DESTROY;
  player->setMaxBomb(curMaxBomb - _increaseBomb);

  std::cout << "bonusBomb end : " << player->getStockBomb() << std::endl;
}

std::string BonusBomb::toString()
{
  std::stringstream ss("");

  ss << "Stock Bomb increase : " << _increaseBomb;
  return ss.str();
}
