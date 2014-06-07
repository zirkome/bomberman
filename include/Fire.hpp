#ifndef FIRE_HPP_
# define FIRE_HPP_

# include "SharedPointer.hpp"
# include "Texture.hpp"
# include "IEntity.hpp"
# include "Cube.hpp"
# include "ResourceManager.hpp"

class Fire : public IEntity
{
private:
  glm::vec2	_vec;
  AObject	*_obj;
  IEntity::Status _status;
  SharedPointer<Texture> _texture;

public:
  Fire(const glm::vec2 &pos);
  virtual ~Fire();
  virtual const glm::vec2 &getPos() const;
  virtual void	setPos(const glm::vec2 &new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock) const;
  virtual IEntity::Type getType() const;
  virtual IEntity::Status getStatus() const;
  virtual void setStatus(IEntity::Status status);
};

#endif /* !FIRE_HPP_ */
