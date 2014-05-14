#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "IEntity.hpp"

class Bomb : public IEntity
{
private:
  int	_x;
  int	_y;

public:
  Bomb(const int, const int y);
  virtual ~Bomb();
  int	getPosX() const;
  int	getPosY() const;
  void	setPosX(const int);
  void	setPosY(const int);
};

#endif /* !BOMB_HPP_ */
