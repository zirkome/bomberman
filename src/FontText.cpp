#include <iostream>
#include <Geometry.hh>
#include "FontText.hpp"

FontText::FontText(const std::string &path)
{
  if (_texture.load(path) == false)
    throw std::runtime_error("Can't load: " + path);
}

void FontText::displayText(const std::string &str, const glm::mat4 &matrice,
                           gdl::AShader *shader) const
{
  // Fill buffers
  const int size = 3;
  gdl::Geometry	geometry;

  for (unsigned int i = 0 ; i < str.length() ; i++)
    {
      float uv_x = (str[i] % 16) / 16.0f;
      float uv_y = (str[i] / 16) / 16.0f;

      geometry.pushVertex(glm::vec3(i * size, size, 0));
      geometry.pushVertex(glm::vec3(i * size, 0, 0));
      geometry.pushVertex(glm::vec3(i * size + size, size, 0));
      geometry.pushVertex(glm::vec3(i * size + size, 0, 0));
      geometry.pushVertex(glm::vec3(i * size + size, size, 0));
      geometry.pushVertex(glm::vec3(i * size, 0, 0));

      geometry.pushUv(glm::vec2(uv_x, 1.0 - uv_y));
      geometry.pushUv(glm::vec2(uv_x, 1 - (uv_y + 1.0 / 16.0)));
      geometry.pushUv(glm::vec2(uv_x + 1.0 / 16.0, 1 - uv_y));
      geometry.pushUv(glm::vec2(uv_x + 1.0 / 16.0, 1 - (uv_y + 1.0 / 16.0)));
      geometry.pushUv(glm::vec2(uv_x + 1.0 / 16.0, 1 - uv_y ));
      geometry.pushUv(glm::vec2(uv_x, 1 - (uv_y + 1.0 / 16.0)));
    }
  geometry.build();
  _texture.bind();

  geometry.draw(*shader, matrice, GL_TRIANGLES);
}
