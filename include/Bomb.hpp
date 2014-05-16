#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "Cube.hpp"
# include "IEntity.hpp"

class Bomb : public IEntity
{
private:
  glm::vec2	_vec;
  AObject *_obj;

public:
  Bomb(const float x, const float y);
  virtual ~Bomb();
  float	getPosX() const;
  float	getPosY() const;
  void	setPosX(const float);
  void	setPosY(const float);
  AObject *getObj();
};

#endif /* !BOMB_HPP_ */
