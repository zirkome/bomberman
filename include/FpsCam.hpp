#ifndef FPSCAM_H
# define FPSCAM_H

# include "config.h"
# include "FreeCam.hpp"

class FpsCam : public FreeCam
{
public:
  FpsCam(const glm::vec3& entPos);
  virtual ~FpsCam();

protected:
  virtual void moveCam(gdl::Input& input, float delta);

private:
  const glm::vec3& _entPos;
};

#endif // FPSCAM_H
