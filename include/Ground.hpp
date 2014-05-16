#ifndef _GROUND_H_
#define _GROUND_H_


# include "IEntity.hpp"
# include "AObject.hpp"

class Ground : public IEntity
{
private:
  glm::vec2	_vec;
  AObject	*_obj;

public:
  Ground(const float x, const float y);
  virtual ~Ground();
  float	getPosX() const;
  float	getPosY() const;
  void	setPosX(const float);
  void	setPosY(const float);
  AObject	*getObj();
};


#endif /* _GROUND_H_ */
