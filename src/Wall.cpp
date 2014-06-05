#include "Wall.hpp"
#include "Cube.hpp"

Wall::Wall(const glm::vec2 &pos) : _vec(pos)
{
  _obj = new Cube();
  _obj->scale(glm::vec3(0.5f, 0.5f, 0.5f));
  _obj->translate(glm::vec3(pos.x, 0, pos.y));
  _texture = AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::WALL);
}

Wall::~Wall()
{
}

const glm::vec2	&Wall::getPos() const
{
  return _vec;
}

void	Wall::setPos(const glm::vec2 &new_pos)
{
  _vec = new_pos;
}

void	Wall::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{

}

void	Wall::draw(gdl::AShader *shader, const gdl::Clock& clock)
{
  _texture->bind();
  _obj->draw(shader, clock);
}

IEntity::Type Wall::getType() const
{
  return IEntity::WALL;
}

IEntity::Status Wall::getStatus() const
{
  return OK;
}

void Wall::setStatus(UNUSED IEntity::Status status)
{

}
