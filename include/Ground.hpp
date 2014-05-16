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
  virtual float	getPosX() const;
  virtual float	getPosY() const;
  virtual void	setPosX(const float);
  virtual void	setPosY(const float);
  virtual AObject	*getObj();
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
};


#endif /* _GROUND_H_ */
