#include <stdexcept>
#include <string>
#include <GL/glew.h>

#include "Texture.hpp"

Texture::Texture(const std::string& path)
  : AResource(path)
{
  if (load(path) == false)
    throw std::runtime_error("Can't load model : " + path);
}

void Texture::bind() const
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  gdl::Texture::bind();
}
