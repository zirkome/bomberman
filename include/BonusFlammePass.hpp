#ifndef _BONUSFLAMMEPASS_H_
#define _BONUSFLAMMEPASS_H_

# include "ABonus.hpp"
# include <string>
# include <sstream>

class BonusFlammePass : public ABonus
{
public:
  BonusFlammePass(const glm::vec2 &pos, double effectTime = 10);
  virtual ~BonusFlammePass();

  void takeAnother(APlayer *);
  void	start(APlayer *player);
  std::string toString();
  void  stop(APlayer *player);
};


#endif /* _BONUSFLAMMEPASS_H_ */
