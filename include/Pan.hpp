#ifndef _PLAN_H_
# define _PLAN_H_

# include <iostream>

# include "AGeometry.hpp"

class Pan : public AGeometry
{
public:
  Pan(const glm::vec2 &repeat = glm::vec2(1, 1));
  virtual ~Pan() {};

private:
  Pan(const Pan& c);
  Pan& operator=(const Pan& c);
};

#endif /* _PLAN_H_ */
