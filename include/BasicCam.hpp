#ifndef _BASICCAM_H_
# define _BASICCAM_H_

# include "ACamera.hpp"

class BasicCam : public ACamera
{
private:
  float _distance;
  float _elevation;
public:
  BasicCam(const glm::vec3 &toFollow, float elevation, float distance);
  virtual ~BasicCam() {};
  virtual void update(const glm::vec3 &toFollow);
};

#endif /* _BASICCAM_H_ */
