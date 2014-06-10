#include "BonusFactory.hpp"

BonusFactory::BonusFactory()
{
}

BonusFactory::~BonusFactory()
{
}

ABonus	*BonusFactory::createBonus(const glm::vec2 &pos, int nbBonus)
{
  int type = rand() % nbBonus;

  // switch (type)
  //   {
  //   case 0:
  //     return new BonusWalk(pos);
  //     break;
  //   case 1:
      return new BonusBomb(pos);
    //   break;
    // case 3:
    //   return new BonusRange(pos);
    //   break;
    // case 4:
    //   return new BonusFlammePass(pos);
    //   break;
    // default:
    //   return new BonusBombPass(pos);
    //   break;
    // }
}
