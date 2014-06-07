#include "SkyBox.hpp"

SkyBox::SkyBox()
{
  _cube.scale(glm::vec3(-2.0f, -2.0f, -2.0f));
}

SkyBox::~SkyBox()
{
}

void SkyBox::update(gdl::Clock const &clock)
{
  _cube.rotate(glm::vec3(1, 1, 0.6), 1.2f * clock.getElapsed());
}

void SkyBox::draw(gdl::AShader *shader, const gdl::Clock &clock,
                  const glm::vec3& pos) const
{
  Cube6Face tmpCube(_cube);

  tmpCube.setPosition(pos);
  AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::SKYBOX)->bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  tmpCube.draw(shader, clock);
}
