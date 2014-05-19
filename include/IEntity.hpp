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
      BOX ,
      WALL,
      BOMB,
      GROUND,
      MODEL,
      NONE
    };
  enum Symbol
    {
      S_BOX = 'o',
      S_WALL = '#'
    };

  virtual ~IEntity() {}
  virtual float getPosX() const = 0;
  virtual float getPosY() const = 0;
  virtual void setPosX(const float) = 0;
  virtual void setPosY(const float) = 0;
  virtual void update(gdl::Input &input, gdl::Clock const &clock) = 0;
  virtual AObject *getObj() = 0;
};

#endif
