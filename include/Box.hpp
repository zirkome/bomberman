#ifndef BOX_HPP_
# define BOX_HPP_

# include "Cube.hpp"
# include "IEntity.hpp"

class Box : public IEntity
{
private:
  int	_x;
  int	_y;
  AObject	*_obj;
public:
  Box(const int, const int y);
  virtual ~Box();
  int	getPosX() const;
  int	getPosY() const;
  void	setPosX(const int);
  void	setPosY(const int);
  AObject *getObj();
};

#endif /* !BOX_HPP_ */
