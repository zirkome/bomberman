#ifndef IENTITY_HPP_
#define IENTITY_HPP_

# include <Clock.hh>
# include <Input.hh>

class	AObject;

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

  virtual void update(gdl::Input &input, gdl::Clock const &clock) = 0;

  virtual int getPosX() const = 0;
  virtual int getPosY() const = 0;
  virtual void setPosX(const int) = 0;
  virtual void setPosY(const int) = 0;
  virtual AObject *getObj() = 0;
};

#endif
