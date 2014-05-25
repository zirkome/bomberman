#include <iostream>
#include <Geometry.hh>
#include "FontText.hpp"

FontText::FontText(const std::string &path, int sizeCharPix)
  : _sizeCharPix(sizeCharPix)
{
  if (_texture.load(path) == false)
    throw std::runtime_error("Can't load: " + path);
}

void FontText::displayText(const std::string &str, const glm::vec4& color,
                           const glm::mat4 &matrice, gdl::AShader *shader) const
{
  const int size = 1;
  const float sizePixf = static_cast<float>(_sizeCharPix);
  gdl::Geometry geometry;

  geometry.setColor(color);

  unsigned int i = 0;
  for (i = 0; i < str.length(); i++)
    {
      float uv_x = (str[i] % _sizeCharPix) / sizePixf;
      float uv_y = (str[i] / _sizeCharPix) / sizePixf;

      geometry.pushVertex(glm::vec3(i * size, size, 0));
      geometry.pushVertex(glm::vec3(i * size, 0, 0));
      geometry.pushVertex(glm::vec3(i * size + size, size, 0));
      geometry.pushVertex(glm::vec3(i * size + size, 0, 0));
      geometry.pushVertex(glm::vec3(i * size + size, size, 0));
      geometry.pushVertex(glm::vec3(i * size, 0, 0));

      geometry.pushNormal(glm::vec3(0, 0, 1));
      geometry.pushNormal(glm::vec3(0, 0, 1));
      geometry.pushNormal(glm::vec3(0, 0, 1));
      geometry.pushNormal(glm::vec3(0, 0, 1));
      geometry.pushNormal(glm::vec3(0, 0, 1));
      geometry.pushNormal(glm::vec3(0, 0, 1));

      geometry.pushUv(glm::vec2(uv_x, 1.0 - uv_y));
      geometry.pushUv(glm::vec2(uv_x, 1 - (uv_y + 1.0 / sizePixf)));
      geometry.pushUv(glm::vec2(uv_x + 1.0 / sizePixf, 1 - uv_y));
      geometry.pushUv(glm::vec2(uv_x + 1.0 / sizePixf, 1 - (uv_y + 1.0 / sizePixf)));
      geometry.pushUv(glm::vec2(uv_x + 1.0 / sizePixf, 1 - uv_y ));
      geometry.pushUv(glm::vec2(uv_x, 1 - (uv_y + 1.0 / sizePixf)));
    }
  geometry.build();
  _texture.bind();

  glm::mat4 mat = glm::scale(matrice, glm::vec3(1.0f / sizePixf, 1.0f / sizePixf, 1.0f));

  geometry.draw(*shader, mat, GL_TRIANGLES);
}
