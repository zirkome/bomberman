#include "config.h"
#include "BasicCam.hpp"

BasicCam::BasicCam(const glm::vec3 &toFollow, float elevation, float distance)
{
  _pos = glm::vec3(0.0, elevation, -distance);
  _forward = glm::vec3(toFollow.x, 0.5, toFollow.y);

  _distance = distance;
  _elevation = elevation;
}

void		BasicCam::update(const glm::vec3 &toFollow)
{
  _pos = glm::vec3(toFollow.x, _elevation, toFollow.y - _distance);
  _forward = glm::vec3(toFollow.x, 0.5, toFollow.y);
}
