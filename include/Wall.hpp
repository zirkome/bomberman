#ifndef WALL_HPP_
# define WALL_HPP_

# include "Texture.hpp"
# include "SharedPointer.hpp"
# include "ResourceManager.hpp"
# include "IEntity.hpp"
# include "AObject.hpp"

class Wall : public IEntity
{
private:
  glm::vec2	_vec;
  AObject	*_obj;
  SharedPointer<Texture> _texture;

public:
  Wall(const glm::vec2 &pos);
  virtual ~Wall();
  virtual const glm::vec2 &getPos() const;
  virtual void	setPos(const glm::vec2 &new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
  virtual IEntity::Type getType() const;
  virtual void setStatus(IEntity::Status status);
  virtual IEntity::Status getStatus() const;
};

#endif /* !WALL_HPP_ */
