#include "TrackCam.hpp"

TrackCam::TrackCam(const glm::vec3& target)
  : _target(target)
{
  _distance = 15;
  _sensivity = 0.4;
  _angley = 0;
  _anglez = 0;
}

TrackCam::~TrackCam()
{
}

void TrackCam::update(gdl::Input& input, const gdl::Clock& clock)
{
  float delta;

  delta = static_cast<float>(clock.getElapsed());

  glm::ivec2 motion = input.getMouseDelta();

  _anglez += static_cast<float>(motion.x) * _sensivity;
  _angley += static_cast<float>(motion.y) * _sensivity;

  if (_angley > 90)
    _angley = 90;
  else if (_angley < -90)
    _angley = -90;

  _pos = glm::vec3(glm::cos(glm::radians(_angley)) * glm::sin(glm::radians(_anglez)),
                   glm::sin(glm::radians(_angley)),
                   glm::cos(glm::radians(_anglez)));

  _pos *= _distance;

  _pos += _target;

  _forward = _target;
}
