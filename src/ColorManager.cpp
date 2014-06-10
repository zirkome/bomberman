#include "ColorManager.hpp"

ColorManager::ColorManager()
  : _index(0)
{
}

ColorManager::~ColorManager()
{
}
void ColorManager::generateColors(int n)
{
  float offset = std::fmod(static_cast<float>(rand()), 10000.0f) + 0.01;

  for (float i = 0.0; i < static_cast<float>(n); i += 1.0)
    {
      float r, g, b;
      r = std::fmod(offset + (0.618033988749895f * i), 1.0f);
      g = std::fmod(offset + (0.618033988749895f * (i + 1)), 1.0f);
      b = std::fmod(offset + (0.618033988749895f * (i + 2)), 1.0f);

      _colors.push_back(glm::vec4(glm::vec3(r, g, b), 1.0f));
    }
}

const glm::vec4& ColorManager::newColor()
{
  if (_index >= static_cast<int>(_colors.size()))
    generateColors(50);
  return _colors[_index++];
}

glm::vec3 ColorManager::interpolateColor(const glm::vec3& a, const glm::vec3& b, float v) const
{
  return (a * v + b * (1.0f - v));
}
