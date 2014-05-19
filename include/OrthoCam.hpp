#ifndef ORTHOCAM_H
# define ORTHOCAM_H

# include "config.h"
# include "ACamera.hpp"

class OrthoCam : public ACamera
{
public:
  OrthoCam();
  virtual ~OrthoCam();

  virtual void update(gdl::Input& input, const gdl::Clock& clock);
  virtual const glm::mat4& project();
protected:
};

#endif // ORTHOCAM_H
