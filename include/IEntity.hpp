#ifndef IENTITY_HPP_
#define IENTITY_HPP_

# include "glm/glm.hpp"

class	AObject;

class IEntity
{
public:
  enum Type
    {
      BOX = 0,
      WALL = 1,
      BOMB = 2,
      NONE = 3
    };
  enum Symbol
    {
      S_BOX = 'o',
      S_WALL = '#'
    };

  virtual ~IEntity() {}
  virtual int getPosX() const = 0;
  virtual int getPosY() const = 0;
  virtual void setPosX(const int) = 0;
  virtual void setPosY(const int) = 0;
  virtual AObject *getObj() = 0;
};

#endif
