#ifndef _CUBE6FACE_H_
# define _CUBE6FACE_H_

# include <Texture.hh>
# include <Geometry.hh>
# include <iostream>

# include "IEntity.hpp"
# include "Cube.hpp"
# include "AssetsManager.hpp"

class Cube6Face : public Cube
{
public:
  Cube6Face();
  virtual ~Cube6Face();
  virtual bool	initialize();
  virtual IEntity::Type getType() const;
  virtual void draw(gdl::AShader *shader, const gdl::Clock &clock);

// private:
//   gdl::Texture *_texture;
//   gdl::Geometry _geometry;
};

#endif /* _CUBE6FACE_H_ */
