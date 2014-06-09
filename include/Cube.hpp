#ifndef _CUBE_H_
# define _CUBE_H_

# include <iostream>

# include "AGeometry.hpp"

class Cube : public AGeometry
{
public:
  Cube();
  virtual ~Cube() {};

private:
  Cube(const Cube& c);
  Cube& operator=(const Cube& c);
};

#endif /* _CUBE_H_ */
