#ifndef _BONUSRANGE_H_
#define _BONUSRANGE_H_

# include "ABonus.hpp"
# include <string>
# include <sstream>

class BonusRange : public ABonus
{
private:
  int	_increaseRange;
  int	_oldRange;
public:
  BonusRange(const glm::vec2 &pos, double effectTime = 10);
  virtual ~BonusRange();

  void takeAnother(APlayer *);
  void	start(APlayer *player);
  std::string toString();
  void  stop(APlayer *player);
};


#endif /* _BONUSRANGE_H_ */
