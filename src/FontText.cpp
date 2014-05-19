#include <iostream>
#include "FontText.hpp"

FontText::FontText(const std::string &path)
{
  if (_texture.load(path) == false)
    throw std::runtime_error("Can't load : " + path);
  _textureID = _texture.getId();

  // Initialize VBO
  glGenBuffers(1, &_vertexBuffID);
  glGenBuffers(1, &_UVBuffID);
}

void FontText::displayText(const std::string &str, glm::vec2 pos, int size, gdl::AShader *shader)
{
  // Initialize Shader
  _shaderID = shader->getProgramId();
  std::cout << "shaderID : " << _shaderID << std::endl;
  // Initialize uniforms' IDs
  _uniformID = shader->getUniformId("fTexture0");
  std::cout << "uniformID : " << _uniformID << std::endl;
  unsigned int length = str.size();

  // Fill buffers
  std::vector<glm::vec2> vertices;
  std::vector<glm::vec2> UVs;
  for (unsigned int i = 0 ; i < length ; i++)
    {
      glm::vec2 vertex_up_left    = glm::vec2( pos.x+i*size     , pos.y+size );
      glm::vec2 vertex_up_right   = glm::vec2( pos.x+i*size+size, pos.y+size );
      glm::vec2 vertex_down_right = glm::vec2( pos.x+i*size+size, pos.y      );
      glm::vec2 vertex_down_left  = glm::vec2( pos.x+i*size     , pos.y      );

      vertices.push_back(vertex_up_left   );
      vertices.push_back(vertex_down_left );
      vertices.push_back(vertex_up_right  );

      vertices.push_back(vertex_down_right);
      vertices.push_back(vertex_up_right);
      vertices.push_back(vertex_down_left);

      char character = str[i];
      float uv_x = (character % 16) / 16.0f;
      float uv_y = (character / 16) / 16.0f;

      glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
      glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
      glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
      glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
      UVs.push_back(uv_up_left   );
      UVs.push_back(uv_down_left );
      UVs.push_back(uv_up_right  );

      UVs.push_back(uv_down_right);
      UVs.push_back(uv_up_right);
      UVs.push_back(uv_down_left);
    }

  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffID);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, _UVBuffID);
  glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

  // Bind shader
  glUseProgram(_shaderID);

  // Bind texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _textureID);
  // Set our "myTextureSampler" sampler to user Texture Unit 0
  glUniform1i(_uniformID, 0);

  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffID);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

  // 2nd attribute buffer : UVs
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, _UVBuffID);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Draw call
  glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

  glDisable(GL_BLEND);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}
