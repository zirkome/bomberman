#ifndef BOX_HPP_
# define BOX_HPP_

# include "Cube.hpp"
# include "IEntity.hpp"

class Box : public IEntity
{
private:
  glm::vec2	_vec;
  AObject	*_obj;

public:
  Box(const float x, const float y);
  virtual ~Box();
  float	getPosX() const;
  float	getPosY() const;
  void	setPosX(const float);
  void	setPosY(const float);
  AObject *getObj();
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
};

#endif /* !BOX_HPP_ */
