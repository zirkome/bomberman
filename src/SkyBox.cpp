#include "ResourceManager.hpp"
#include "Texture.hpp"
#include "SkyBox.hpp"
#include "config.h"

SkyBox::SkyBox()
{
  scale(glm::vec3(-2.0f, -2.0f, -2.0f));
  _texture = ResourceManager::getInstance()->get<Texture>(RES_TEXTURE "skybox.tga");
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
  _texture->bind();
  tmpCube.draw(shader, clock);
}
