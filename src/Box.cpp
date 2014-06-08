#include "ResourceManager.hpp"
#include "Box.hpp"
#include "config.h"

Box::Box(const glm::vec2 &pos) : _vec(pos)
{
  _status = OK;
  _obj = new Cube();
  _obj->scale(glm::vec3(0.5f, 0.5f, 0.5f));
  _obj->translate(glm::vec3(pos.x, 0, pos.y));

  _texture = ResourceManager::getInstance()->get<Texture>(RES_TEXTURE "box_texture.tga");
}

Box::~Box()
{
  delete _obj;
}

const glm::vec2	&Box::getPos() const
{
  return _vec;
}

void	Box::setPos(const glm::vec2 &new_pos)
{
  _vec = new_pos;
}

void	Box::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{
}

void	Box::draw(gdl::AShader *shader, const gdl::Clock& clock) const
{
  _texture->bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  _obj->draw(shader, clock);
}

IEntity::Type Box::getType() const
{
  return IEntity::BOX;
}

IEntity::Status Box::getStatus() const
{
  return _status;
}

void Box::setStatus(IEntity::Status status)
{
  _status = status;
}
