#include "Fire.hpp"
#include "config.h"

Fire::Fire(const glm::vec2 &pos) : _vec(pos)
{
  _status = OK;
  _obj = new Cube();
  _texture = ResourceManager::getInstance()->get<Texture>(RES_TEXTURE "fire.tga");

  _obj->scale(glm::vec3(0.5f, 0.5f, 0.5f));
  _obj->translate(glm::vec3(pos.x, 0, pos.y));
}

Fire::~Fire()
{

}

const glm::vec2	&Fire::getPos() const
{
  return _vec;
}

void	Fire::setPos(const glm::vec2 &new_pos)
{
  _obj->translate(glm::vec3(new_pos.x - _vec.x, 0, new_pos.y - _vec.y));
  _vec = new_pos;
}

void	Fire::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{
}

void	Fire::draw(gdl::AShader *shader, const gdl::Clock& clock) const
{
  _texture->bind();
  _obj->draw(shader, clock);
}

IEntity::Type Fire::getType() const
{
  return IEntity::WALL;
}

IEntity::Status Fire::getStatus() const
{
  return _status;
}

void Fire::setStatus(IEntity::Status status)
{
  _status = status;
}
