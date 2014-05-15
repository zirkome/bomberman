#ifndef IENTITY_HPP_
#define IENTITY_HPP_

# include "glm/glm.hpp"

class IEntity
{
public:
  enum Type
    {
      BOX = 0,
      WALL = 1,
      NONE = 2
    };

  virtual ~IEntity() {}
  virtual int getPosX() const = 0;
  virtual int getPosY() const = 0;
  virtual void setPosX(const int) = 0;
  virtual void setPosY(const int) = 0;
};

#endif
