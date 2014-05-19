#ifndef _CUBE_H_
#define _CUBE_H_

#include "IEntity.hpp"
#include "AObject.hpp"
#include "AssetsManager.hpp"
#include <Texture.hh>
#include <Geometry.hh>
#include <iostream>

class Cube : public AObject
{
private:
  gdl::Texture *_texture;
  gdl::Geometry _geometry;
public:
  Cube();
  virtual ~Cube();
  virtual bool	initialize();

  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
};

#endif /* _CUBE_H_ */
