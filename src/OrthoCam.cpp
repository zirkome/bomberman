#include "OrthoCam.hpp"

OrthoCam::OrthoCam()
{
}

OrthoCam::~OrthoCam()
{
}

void OrthoCam::update(UNUSED gdl::Input& input, UNUSED const gdl::Clock& clock)
{
}

const glm::mat4& OrthoCam::project()
{
  _proj = glm::ortho(-50.0f * float(16 / 9), 50.0f * float(16 / 9), -50.0f, 50.0f, -100.0f, 100.0f);
  return _proj;
}
