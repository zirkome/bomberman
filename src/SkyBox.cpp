#include "ResourceManager.hpp"
#include "Texture.hpp"
#include "SkyBox.hpp"
#include "config.h"

SkyBox::SkyBox()
{
  _cube = new GameGeometry(ResourceManager::getInstance()->get<AGeometry>("cube6Face.geo"));
  _cube->scale(glm::vec3(-2.0f, -2.0f, -2.0f));
  _texture = ResourceManager::getInstance()->get<Texture>(RES_TEXTURE "skybox.tga");
}

SkyBox::~SkyBox()
{
  delete _cube;
}

void SkyBox::update(gdl::Clock const &clock)
{
  _cube->rotate(glm::vec3(1, 1, 0.6), 1.2f * clock.getElapsed());
}

void SkyBox::draw(gdl::AShader *shader, const gdl::Clock &clock,
                  const glm::vec3& pos) const
{
  GameGeometry tmpCube(*_cube);

  tmpCube.setPosition(pos);
  _texture->bind();
  tmpCube.draw(shader, clock);
}
