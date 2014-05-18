#include "FpsCam.hpp"

FpsCam::FpsCam(const glm::vec3& entPos)
  : _entPos(entPos)
{
}

FpsCam::~FpsCam()
{
}

void FpsCam::moveCam(UNUSED gdl::Input& input, UNUSED float delta)
{
  _pos = _entPos;
}