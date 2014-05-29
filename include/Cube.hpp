#ifndef _CUBE_H_
# define _CUBE_H_

# include <Texture.hh>
# include <Geometry.hh>
# include <iostream>

# include "IEntity.hpp"
# include "AObject.hpp"
# include "AssetsManager.hpp"

class Cube : public AObject
{
public:
  Cube();
  virtual ~Cube();
  virtual bool	initialize();
  virtual IEntity::Type getType() const;
  virtual void draw(gdl::AShader *shader, const gdl::Clock &clock);

protected:
  gdl::Texture *_texture;
  gdl::Geometry _geometry;
};

#endif /* _CUBE_H_ */
