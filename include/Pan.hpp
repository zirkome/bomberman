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
  const glm::vec2	&_repeat;

public:
  Pan(const glm::vec2 &repeat = glm::vec2(1, 1));

  virtual ~Pan();
  virtual bool	initialize();

  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
  void	draw(gdl::AShader *shader);
};

#endif /* _PLAN_H_ */
