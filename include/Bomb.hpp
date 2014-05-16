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
  Bomb(const int x, const int y);
  virtual ~Bomb();

  virtual void	update(gdl::Input &input, gdl::Clock const &clock);
  virtual int	getPosX() const;
  virtual int	getPosY() const;
  virtual void	setPosX(const int);
  virtual void	setPosY(const int);
  virtual AObject *getObj();
};

#endif /* !BOMB_HPP_ */
