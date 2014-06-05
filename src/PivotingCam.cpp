#include "PivotingCam.hpp"

PivotingCam::PivotingCam(const glm::vec2 &toFollow, float elevation, float distance)
{
  _pos = glm::vec3(0.0, elevation, -distance);
  _forward = glm::vec3(toFollow.x, 0.5, toFollow.y);

  _distance = distance;
  _elevation = elevation;
}

void		PivotingCam::update(const glm::vec2 &toFollow)
{
  _forward = glm::vec3(toFollow.x, 0.5, toFollow.y);
}
