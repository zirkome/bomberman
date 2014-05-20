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
      glm::vec3 vertex_up_left    = glm::vec3( pos.x+i*size     , pos.y+size , pos.z);
      glm::vec3 vertex_up_right   = glm::vec3( pos.x+i*size+size, pos.y+size , pos.z);
      glm::vec3 vertex_down_right = glm::vec3( pos.x+i*size+size, pos.y      , pos.z);
      glm::vec3 vertex_down_left  = glm::vec3( pos.x+i*size     , pos.y      , pos.z);

      geometry.pushVertex(vertex_up_left   );
      geometry.pushVertex(vertex_down_left );
      geometry.pushVertex(vertex_up_right  );

      geometry.pushVertex(vertex_down_right);
      geometry.pushVertex(vertex_up_right);
      geometry.pushVertex(vertex_down_left);

      char character = str[i];
      float uv_x = (character % 16) / 16.0f;
      float uv_y = (character / 16) / 16.0f;

      glm::vec2 uv_up_left    = glm::vec2( uv_x           , 1 - uv_y );
      glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, 1 - uv_y );
      glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, 1 - (uv_y + 1.0f/16.0f) );
      glm::vec2 uv_down_left  = glm::vec2( uv_x           , 1 - (uv_y + 1.0f/16.0f) );

      geometry.pushUv(uv_up_left   );
      geometry.pushUv(uv_down_left );
      geometry.pushUv(uv_up_right  );

      geometry.pushUv(uv_down_right);
      geometry.pushUv(uv_up_right);
      geometry.pushUv(uv_down_left);
    }
  geometry.build();
  _texture.bind();

  // glDisable(GL_DEPTH)
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  geometry.draw(*shader, glm::mat4(1), GL_TRIANGLES);

  glDisable(GL_BLEND);
}
