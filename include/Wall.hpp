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

  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual int	getPosX() const;
  virtual int	getPosY() const;
  virtual void	setPosX(const int);
  virtual void	setPosY(const int);
  virtual AObject	*getObj();
};

#endif /* !WALL_HPP_ */
