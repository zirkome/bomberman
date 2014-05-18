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
  virtual float	getPosX() const;
  virtual float	getPosY() const;
  virtual void	setPosX(const float);
  virtual void	setPosY(const float);
  virtual AObject *getObj();
  virtual void	update(gdl::Input &input, gdl::Clock const &clock);
};

#endif /* !BOMB_HPP_ */
