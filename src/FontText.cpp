#include <iostream>
#include <Geometry.hh>
#include "FontText.hpp"

FontText::FontText(const std::string &path)
{
  if (_texture.load(path) == false)
    throw std::runtime_error("Can't load : " + path);
  // _textureID = _texture.getId();

  // // Initialize VBO
  // glGenBuffers(1, &_vertexBuffID);
  // glGenBuffers(1, &_UVBuffID);
}

void FontText::displayText(const std::string &str, const glm::vec3 &pos, int size, gdl::AShader *shader)
{
  // Fill buffers
  gdl::Geometry	geometry;

  for (unsigned int i = 0 ; i < str.length() ; i++)
    {
      float uv_x = (str[i] % 16) / 16.0f;
      float uv_y = (str[i] / 16) / 16.0f;

      geometry.pushVertex(glm::vec3(pos.x + i * size, pos.y + size , pos.z));
      geometry.pushVertex(glm::vec3(pos.x + i * size, pos.y, pos.z));
      geometry.pushVertex(glm::vec3(pos.x + i * size + size, pos.y + size, pos.z));
      geometry.pushVertex(glm::vec3(pos.x + i * size + size, pos.y, pos.z));
      geometry.pushVertex(glm::vec3(pos.x + i * size + size, pos.y + size, pos.z));
      geometry.pushVertex(glm::vec3(pos.x + i * size, pos.y, pos.z));

      geometry.pushUv(glm::vec2(uv_x, 1.0 - uv_y));
      geometry.pushUv(glm::vec2(uv_x, 1 - (uv_y + 1.0 / 16.0)));
      geometry.pushUv(glm::vec2(uv_x + 1.0 / 16.0, 1 - uv_y));
      geometry.pushUv(glm::vec2(uv_x + 1.0 / 16.0, 1 - (uv_y + 1.0 / 16.0)));
      geometry.pushUv(glm::vec2(uv_x + 1.0 / 16.0, 1 - uv_y ));
      geometry.pushUv(glm::vec2(uv_x, 1 - (uv_y + 1.0 / 16.0)));
    }

  geometry.build();
  _texture.bind();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  geometry.draw(*shader, glm::mat4(1), GL_TRIANGLES);

  glDisable(GL_BLEND);
}
