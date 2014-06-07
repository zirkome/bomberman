#include "ResourceManager.hpp"
#include "Texture.hpp"
#include "SkyBox.hpp"

SkyBox::SkyBox()
{
  scale(glm::vec3(-2.0f, -2.0f, -2.0f));
  _texture = ResourceManager::getInstance()->get<Texture>(RES_TEXTURE "skybox.tga");
}

SkyBox::~SkyBox()
{
}

void SkyBox::draw(gdl::AShader *shader, const gdl::Clock &clock)
{
  _texture->bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  Cube6Face::draw(shader, clock);
}
