#ifndef IENTITY_HPP_
#define IENTITY_HPP_

class IEntity
{
public:
  ~IEntity() {}
  virtual int somethings() = 0;
};

#endif
