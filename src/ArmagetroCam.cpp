#include <iostream>
#include "ArmagetroCam.hpp"

ArmagetroCam::ArmagetroCam(const glm::vec2 &playerPos)
{
  _pos.x = playerPos.x;
  _pos.z = -playerPos.y;
  _pos.y = 10;

  _forward = glm::vec3(playerPos.x, 0.5, playerPos.y);
  _follow_pos.clear();
}

void	ArmagetroCam::update(gdl::Input &input, const gdl::Clock &clock)
{

}

void	ArmagetroCam::update(const glm::vec2 &newPlayerPos)
{
  if (newPlayerPos != _follow_pos.back())
    {
      _follow_pos.push_back(newPlayerPos);

      if (_follow_pos.size() > 40)
	{
	  glm::vec2 tmp = _follow_pos.front();

	  _pos.x = tmp.x;
	  _pos.z = tmp.y;
	  _follow_pos.pop_front();
	}
      _forward.x = newPlayerPos.x;
      _forward.z = newPlayerPos.y;
      _forward.y = 0.5;
    }
}
