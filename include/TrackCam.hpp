#ifndef TRACKCAM_H
# define TRACKCAM_H

# include "ACamera.hpp"
# include <glm/gtx/rotate_vector.hpp>

# include <SdlContext.hh>

class TrackCam : public ACamera
{
public:
  TrackCam(const glm::vec3& target = glm::vec3(0, 0, 0));
  virtual ~TrackCam();

  void setTarget(const glm::vec3& targ) {_target = targ;};
  void setDistance(float dist) {_distance = dist;};

  virtual void update(gdl::Input& input, const gdl::Clock& clock);

protected:
  glm::vec3 _target;
  float _distance;
  float _sensivity;
  float _angley;
  float _anglez;
};

#endif // TRACKCAM_H
