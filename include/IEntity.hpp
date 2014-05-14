#ifndef IENTITY_HPP_
#define IENTITY_HPP_

class IEntity
{
public:
  virtual ~IEntity() {}
  virtual int getPosX() const = 0;
  virtual int getPosY() const = 0;
  virtual void setPosX(const int) = 0;
  virtual void setPosY(const int) = 0;
};

#endif
