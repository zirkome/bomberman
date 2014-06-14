#ifndef _BONUSCOIN_H_
#define _BONUSCOIN_H_


# include "ABonus.hpp"
# include <string>
# include <sstream>

class BonusCoin : public ABonus
{
private:
  int	_increase;
  int	_oldScores;
public:
  BonusCoin(const glm::vec2 &pos, double effectTime = 5);
  virtual ~BonusCoin();

  void  takeAnother(APlayer *player);
  void	start(APlayer *player);
  std::string toString();
  void  stop(APlayer *player);
};


#endif /* _BONUSCOIN_H_ */
