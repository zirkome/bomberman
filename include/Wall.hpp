#ifndef WALL_HPP_
# define WALL_HPP_

# include "Texture.hh"
# include "IEntity.hpp"
# include "AObject.hpp"

class Wall : public IEntity
{
private:
  glm::vec2	_vec;
  AObject	*_obj;
  gdl::Texture	*_texture;

public:
  Wall(glm::vec2 pos);
  virtual ~Wall();
  virtual glm::vec2	getPos() const;
  virtual void	setPos(glm::vec2 new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
};

#endif /* !WALL_HPP_ */
