#ifndef _BONUSWALK_H_
#define _BONUSWALK_H_

# include "ABonus.hpp"
# include <string>
# include <sstream>

class BonusWalk : public ABonus
{
private:
  double	_increaseSpeed;
  BonusType	_typeWalk;
public:
  BonusWalk(BonusType typeWalk, glm::vec2 pos, double effectTime);
  virtual ~BonusWalk();

  void	start(APlayer *player);
  void  update(APlayer *player, const gdl::Clock &clock);
  std::string toString();
  void  stop(APlayer *player);
};

#endif /* _BONUSWALK_H_ */
