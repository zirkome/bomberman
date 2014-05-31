#ifndef _PIVOTINGCAM_H_
# define _PIVOTINGCAM_H_

# include "ACamera.hpp"

class PivotingCam : public ACamera
{
private:
  float _distance;
  float	_elevation;
public:
  PivotingCam(const glm::vec2 &toFollow, float elevation, float distance);
  virtual ~PivotingCam() {}
  virtual void update(UNUSED gdl::Input& input, UNUSED const gdl::Clock& clock) {};
  virtual void update(const glm::vec2 &toFollow);
};

#endif /* _PIVOTINGCAM_H_ */
