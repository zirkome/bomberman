#include "Ground.hpp"
#include "Pan.hpp"

Ground::Ground(glm::vec2 pos) : _vec(pos)
{
  _obj = new Pan();
  _obj->initialize();
  _obj->translate(glm::vec3(pos.x, 0, pos.y));
  _texture = AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::GROUND);
}

Ground::~Ground()
{

}

glm::vec2	Ground::getPos() const
{
  return _vec;
}

void	Ground::setPos(glm::vec2 new_pos)
{
  _vec = new_pos;
}

void Ground::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{

}

void Ground::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  _texture->bind();
  _obj->draw(shader, clock);
}
