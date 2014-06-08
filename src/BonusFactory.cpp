#include "BonusFactory.hpp"

BonusFactory::BonusFactory()
{
}

BonusFactory::~BonusFactory()
{
}

ABonus	*BonusFactory::createBonus(const glm::vec2 &pos, int nbBonus)
{
  ABonus::BonusType type = static_cast<ABonus::BonusType>(rand() % nbBonus);

  switch (type)
    {
    case ABonus::FASTER:
    case ABonus::SLOWLY:
      return new BonusWalk(type, pos, 10);
      break;
    default:
      return new BonusWalk(ABonus::FASTER, pos, 10);
      break;
    }
}
