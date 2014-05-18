#ifndef _PLAN_H_
#define _PLAN_H_

#include "IEntity.hpp"
#include "AObject.hpp"
#include "AssetsManager.hpp"
#include <Texture.hh>
#include <Geometry.hh>
#include <iostream>

class Pan : public AObject
{
private:
  gdl::Texture *_texture;
  gdl::Geometry _geometry;

public:
  Pan(IEntity::Type assetsType);
  virtual ~Pan();
  virtual bool	initialize();

  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
};

#endif /* _PLAN_H_ */
