#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "Cube.hpp"
# include "IEntity.hpp"

class Bomb : public IEntity
{
private:
  int	_x;
  int	_y;
  glm::vec2	_vec;
  AObject *_obj;
public:
  Bomb(const int, const int y);
  virtual ~Bomb();
  int	getPosX() const;
  int	getPosY() const;
  void	setPosX(const int);
  void	setPosY(const int);
  AObject *getObj();
};

#endif /* !BOMB_HPP_ */
