#ifndef COLORMANAGER_H
# define COLORMANAGER_H

# include <cmath>
# include <vector>
# include <glm/glm.hpp>

class ColorManager
{
public:
  ColorManager();
  virtual ~ColorManager();

  const glm::vec4& newColor();
private:
  void generateColors(int n);
  glm::vec3 interpolateColor(const glm::vec3& a, const glm::vec3& b, float v) const;

private:
  int _index;
  std::vector<glm::vec4> _colors;
};

#endif // COLORMANAGER_H
