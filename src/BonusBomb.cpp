#include "BonusBomb.hpp"

BonusBomb::BonusBomb(const glm::vec2 &pos, double effectTime)
  : ABonus(MULTI_BOMB, pos, effectTime)
{
  _oldStockBomb = 0;
  _oldMaxBomb = 0;
  _increaseBomb = 3;
}

BonusBomb::~BonusBomb()
{
}

void	BonusBomb::start(APlayer *player)
{
  _oldStockBomb = player->getStockBomb();
  _oldMaxBomb = player->getMaxBomb();

  player->setMaxBomb(_oldMaxBomb + _increaseBomb);
  player->setStockBomb(_oldMaxBomb + _increaseBomb);

  _status = REMOVE;
}

void	BonusBomb::stop(APlayer *player)
{
  double curMaxBomb = player->getMaxBomb();

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
