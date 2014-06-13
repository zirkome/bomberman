#ifndef BONUSFIREBALL_HPP_
# define BONUSFIREBALL_HPP_

# include "ABonus.hpp"
# include <string>
# include <sstream>

class BonusFireBall : public ABonus
{
public:
  BonusFireBall(const glm::vec2 &pos, double effectTime = 10);
  virtual ~BonusFireBall();
  void takeAnother(APlayer *player);
  void start(APlayer *player);
  std::string toString();
  void stop(APlayer *player);

};

#endif /* !BONUSFIREBALL_HPP_ */
