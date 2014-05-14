#ifndef WALL_HPP_
# define WALL_HPP_

# include "IEntity.hpp"
# include "AObject.hpp"

class Wall : public IEntity
{
private:
  int		_x;
  int		_y;
  AObject	*_obj;
public:
  Wall(const int, const int y);
  virtual ~Wall();
  int	getPosX() const;
  int	getPosY() const;
  void	setPosX(const int);
  void	setPosY(const int);
};

#endif /* !WALL_HPP_ */
