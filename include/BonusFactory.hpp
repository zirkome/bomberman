#ifndef _BONUSFACTORY_H_
#define _BONUSFACTORY_H_

# include "Singleton.hpp"

# include "BonusWalk.hpp"
# include "BonusBomb.hpp"
# include "BonusRange.hpp"
# include "BonusFlammePass.hpp"
# include "BonusBombPass.hpp"

class BonusFactory : public Singleton<BonusFactory>
{
  friend BonusFactory* Singleton<BonusFactory>::getInstance();
  friend void Singleton<BonusFactory>::kill();

public:
  ABonus *createBonus(const glm::vec2 &pos, int nbBonus);
private:
  template<class T>
  ABonus* instanciateBonus(const glm::vec2 &pos) const;
  BonusFactory();
  virtual ~BonusFactory();
private:
  std::vector<ABonus* (BonusFactory::*)(const glm::vec2 &pos) const> _bonus;
};

template<class T>
ABonus* BonusFactory::instanciateBonus(const glm::vec2 &pos) const
{
  return new T(pos);
}

#endif /* _BONUSFACTORY_H_ */
