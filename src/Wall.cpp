#include "Wall.hpp"
#include "Cube.hpp"

Wall::Wall(glm::vec2 pos) : _vec(pos)
{
  _obj = new Cube();
  _obj->initialize();
  _obj->translate(glm::vec3(pos.x, 0, pos.y));
  _texture = AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::WALL);
}

Wall::~Wall()
{

}

glm::vec2	Wall::getPos() const
{
  return _vec;
}

void	Wall::setPos(glm::vec2 new_pos)
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
