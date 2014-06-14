#ifndef _BONUSBOMBPASS_H_
#define _BONUSBOMBPASS_H_

# include "ABonus.hpp"
# include <string>
# include <sstream>

class BonusBombPass : public ABonus
{
public:
  BonusBombPass(const glm::vec2 &pos, double effectTime = 10);
  virtual ~BonusBombPass();

  void takeAnother(APlayer *);
  void	start(APlayer *player);
  std::string toString();
  void  stop(APlayer *player);
};


#endif /* _BONUSBOMBPASS_H_ */
