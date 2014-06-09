#ifndef _BONUSBOMB_H_
#define _BONUSBOMB_H_

# include "ABonus.hpp"
# include <string>
# include <sstream>

class BonusBomb : public ABonus
{
private:
  int	_increaseBomb;
  int	_oldStockBomb;
  int	_oldMaxBomb;
public:
  BonusBomb(const glm::vec2 &pos, double effectTime = 10);
  virtual ~BonusBomb();

  void	start(APlayer *player);
  std::string toString();
  void  stop(APlayer *player);
};

#endif /* _BONUSBOMB_H_ */
