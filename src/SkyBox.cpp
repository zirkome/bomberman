#include "SkyBox.hpp"

SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}

void SkyBox::draw(gdl::AShader *shader, const gdl::Clock &clock)
{
  AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::SKYBOX)->bind();
  Cube6Face::draw(shader, clock);
}
