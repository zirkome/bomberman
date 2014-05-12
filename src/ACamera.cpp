#include "ACamera.hpp"

ACamera::ACamera(const glm::vec3& pos, const glm::vec3& forward)
  : _pos(pos), _forward(forward)
{
  _up = glm::vec3(0, 1, 0);
}

ACamera::~ACamera()
{
}

void ACamera::setPosition(const glm::vec3& pos)
{
  _pos = pos;
}

void ACamera::setForward(const glm::vec3& forw)
{
  _forward = forw;
}

void ACamera::setUp(const glm::vec3& up)
{
  _up = up;
}

const glm::mat4& ACamera::project()
{
  _proj =  glm::lookAt(_pos, _forward, _up);
  return _proj;
}

void ACamera::translate(const glm::vec3& pos)
{
  setPosition(_pos + pos);
}
