#ifndef BONUS_HPP_
# define BONUS_HPP_

# include "ABonus.hpp"

class Bonus : public ABonus
{
public:
  Bonus(const glm::vec2 &pos);
  virtual ~Bonus();
  virtual void	action(APlayer *);
};

#endif /* !BONUS_HPP_ */
