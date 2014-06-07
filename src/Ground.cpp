#include "Ground.hpp"
#include "Pan.hpp"

Ground::Ground(const glm::vec2 &pos)
  : _vec(pos)
{
  _obj = new Pan;
  _obj->translate(glm::vec3(pos.x, -0.5f, pos.y));
  _obj->scale(glm::vec3(0.5f, 0.5f, 1.0));
  _obj->rotate(glm::vec3(1, 0, 0), 90.0);
  _texture = AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::GROUND);
}

Ground::~Ground()
{

}

const glm::vec2	&Ground::getPos() const
{
  return _vec;
}

void	Ground::setPos(const glm::vec2 &new_pos)
{
  _vec = new_pos;
}

void Ground::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{

}

void Ground::draw(gdl::AShader *shader, const gdl::Clock& clock) const
{
  _texture->bind();
  _obj->draw(shader, clock);
}

IEntity::Type Ground::getType() const
{
  return IEntity::GROUND;
}

IEntity::Status Ground::getStatus() const
{
  return OK;
}

void Ground::setStatus(UNUSED IEntity::Status status)
{
}
