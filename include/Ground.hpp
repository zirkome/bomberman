#ifndef _GROUND_H_
#define _GROUND_H_


# include "IEntity.hpp"
# include "AObject.hpp"

class Ground : public IEntity
{
private:
  int		_x;
  int		_y;
  AObject	*_obj;
public:
  Ground(const int, const int y);
  virtual ~Ground();

  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual int	getPosX() const;
  virtual int	getPosY() const;
  virtual void	setPosX(const int);
  virtual void	setPosY(const int);
  virtual AObject	*getObj();
};


#endif /* _GROUND_H_ */
