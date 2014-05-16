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
  float	getPosX() const;
  float	getPosY() const;
  void	setPosX(const float);
  void	setPosY(const float);
  AObject	*getObj();
};

#endif /* !WALL_HPP_ */
