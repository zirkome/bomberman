#include "FreeCam.hpp"

#include <cmath>

FreeCam::FreeCam()
{
  _speed = 2.5;
  _phi = 0;
  _theta = 88;
  _sensivity = 0.4;
  _target = _forward;
  vectorsFromAngles();
}

FreeCam::~FreeCam()
{
}

void FreeCam::update(gdl::Input& input, const gdl::Clock& clock)
{
  float delta;

  delta = static_cast<float>(clock.getElapsed());

  glm::ivec2 motion = input.getMouseDelta();
  _theta += (_sensivity * static_cast<float>(motion.x));
  _phi -= (_sensivity * static_cast<float>(motion.y));
  vectorsFromAngles();

  moveCam(input, delta);
}

void FreeCam::moveCam(gdl::Input & input, float delta)
{
  if (input.getKey(SDLK_UP))
    translate(_target * (_speed * delta));
  if (input.getKey(SDLK_DOWN))
    translate(-_target * (_speed * delta));
  if (input.getKey(SDLK_LEFT))
    translate(_left * (_speed * delta));
  if (input.getKey(SDLK_RIGHT))
    translate(-_left * (_speed * delta));

  _forward = _pos + _target;
}

void FreeCam::vectorsFromAngles()
{
  if (_phi > 89.89)
    _phi = 89.89;
  else if (_phi < -89.89)
    _phi = -89.89;

  double r_temp = cos(_phi * M_PI / 180);
  double up_angle_temp = sin(_phi * M_PI / 180);
  double side_angletemp1 = r_temp * sin(_theta * M_PI / 180);
  double side_angletemp2 = r_temp * cos(_theta * M_PI / 180);

  _target.x = (_up.x * up_angle_temp) + (_up.z * side_angletemp1) + (_up.y * side_angletemp2);
  _target.y = (_up.y * up_angle_temp) + (_up.x * side_angletemp1) + (_up.z * side_angletemp2);
  _target.z = (_up.z * up_angle_temp) + (_up.y * side_angletemp1) + (_up.x * side_angletemp2);

  _left = glm::normalize(glm::cross(_up, _target));

  _forward = _pos + _target;
}
