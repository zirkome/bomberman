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
  Cube(gdl::Geometry* geometry);
  Cube(const Cube& c);
  const Cube& operator=(const Cube& c);

  Cube();
  Cube(const glm::vec4 &color);
  virtual ~Cube();

  virtual void draw(gdl::AShader *shader, const gdl::Clock &clock);

private:
  gdl::Geometry* _geometry;
};

#endif /* _CUBE_H_ */
