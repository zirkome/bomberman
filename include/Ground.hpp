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
  int	getPosX() const;
  int	getPosY() const;
  void	setPosX(const int);
  void	setPosY(const int);
  AObject	*getObj();
};


#endif /* _GROUND_H_ */
