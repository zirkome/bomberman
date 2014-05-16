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

  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual int	getPosX() const;
  virtual int	getPosY() const;
  virtual void	setPosX(const int);
  virtual void	setPosY(const int);
  virtual AObject *getObj();
};

#endif /* !BOX_HPP_ */
