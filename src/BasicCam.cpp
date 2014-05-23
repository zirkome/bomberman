#include "BasicCam.hpp"

BasicCam::BasicCam(const glm::vec2 &toFollow, float elevation, float distance)
{
  _pos = glm::vec3(toFollow.x, elevation, toFollow.y - distance);
  _forward = glm::vec3(toFollow.x, 0.5, toFollow.y);

  _distance = distance;
  _elevation = elevation;
}

void		BasicCam::update(const glm::vec2 &toFollow)
{
  _pos = glm::vec3(toFollow.x, _elevation, toFollow.y - _distance);
  _forward = glm::vec3(toFollow.x, 0.5, toFollow.y);
}

void		BasicCam::update(__attribute__((unused)) gdl::Input& input,
				 __attribute__((unused)) const gdl::Clock& clock)
{

}
