#ifndef _BONUSWALK_H_
#define _BONUSWALK_H_

# include "ABonus.hpp"
# include <string>
# include <sstream>

class BonusWalk : public ABonus
{
private:
  double	_increaseSpeed;
public:
  BonusWalk(const glm::vec2 &pos, double effectTime = 10);
  virtual ~BonusWalk();

  void	start(APlayer *player);
  std::string toString();
  void  stop(APlayer *player);
};

#endif /* _BONUSWALK_H_ */
