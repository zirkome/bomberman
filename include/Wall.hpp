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
  Wall(const glm::vec2 &pos);
  virtual ~Wall();
  virtual const glm::vec2 &getPos() const;
  virtual void	setPos(const glm::vec2 &new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
  virtual IEntity::Type getType() const;
};

#endif /* !WALL_HPP_ */
