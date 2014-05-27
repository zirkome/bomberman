#ifndef BOX_HPP_
# define BOX_HPP_

# include "Cube.hpp"
# include "IEntity.hpp"

class Box : public IEntity
{
private:
  glm::vec2	_vec;
  AObject	*_obj;
  gdl::Texture	*_texture;

public:
  Box(const glm::vec2 &pos);
  virtual ~Box();
  virtual const glm::vec2 &getPos() const;
  virtual void setPos(const glm::vec2 &new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual void draw(gdl::AShader *shader, const gdl::Clock& clock);
  virtual IEntity::Type getType() const;
};

#endif /* !BOX_HPP_ */
