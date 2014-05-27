#include "SkyBox.hpp"

SkyBox::SkyBox()
{
  scale(glm::vec3(2.0f, 2.0f, 2.0f));
}

SkyBox::~SkyBox()
{
}

void SkyBox::draw(gdl::AShader *shader, const gdl::Clock &clock)
{
  AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::SKYBOX)->bind();
  Cube6Face::draw(shader, clock);
}
