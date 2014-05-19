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
  Box(glm::vec2 pos);
  virtual ~Box();
  virtual glm::vec2	getPos() const;
  virtual void	setPos(glm::vec2 new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
};

#endif /* !BOX_HPP_ */
