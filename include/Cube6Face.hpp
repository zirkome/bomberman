#ifndef _CUBE6FACE_H_
# define _CUBE6FACE_H_

# include <iostream>
# include <Texture.hh>
# include <Geometry.hh>

# include "IEntity.hpp"
# include "AGeometry.hpp"

class Cube6Face : public AGeometry
{
public:
  Cube6Face();
  virtual ~Cube6Face() {};

private:
  Cube6Face(const Cube6Face& c);
  Cube6Face& operator=(const Cube6Face& c);
};

#endif /* _CUBE6FACE_H_ */
