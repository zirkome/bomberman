#include "BonusCoin.hpp"

BonusCoin::BonusCoin(const glm::vec2 &pos, double effectTime)
  : ABonus(COIN, pos, effectTime)
{
  _oldScores = 0;
  _increase = 0;
}

BonusCoin::~BonusCoin()
{
}

void	BonusCoin::start(APlayer *player)
{
  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);

  _oldScores = player->getScores();

  _increase += 3;
  player->increaseScores(3);
}

void	BonusCoin::stop(UNUSED APlayer *player)
{
  _status = DESTROY;
}

void    BonusCoin::takeAnother(APlayer *player)
{
  double	effectTime = _effectTime.getTime();

  SoundManager::getInstance()->manageSound(SoundManager::GET_ITEM, SoundManager::PLAY);
  _increase += 3;
  _effectTime.reset(effectTime);
  player->increaseScores(3);
}

std::string BonusCoin::toString()
{
  std::stringstream ss("");

  ss << "Scores increase to" << _oldScores + _increase;
  return ss.str();
}
