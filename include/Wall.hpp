#ifndef WALL_HPP_
# define WALL_HPP_

# include "IEntity.hpp"
# include "AObject.hpp"

class Wall : public IEntity
{
private:
  glm::vec2	_vec;
  AObject	*_obj;

public:
  Wall(const float x, const float y);
  virtual ~Wall();
  virtual float	getPosX() const;
  virtual float	getPosY() const;
  virtual void	setPosX(const float);
  virtual void	setPosY(const float);
  virtual AObject *getObj();
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
};

#endif /* !WALL_HPP_ */
