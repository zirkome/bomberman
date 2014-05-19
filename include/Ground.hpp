#ifndef _GROUND_H_
#define _GROUND_H_

# include <Texture.hh>
# include "IEntity.hpp"
# include "AObject.hpp"

class Ground : public IEntity
{
private:
  glm::vec2	_vec;
  AObject	*_obj;
  gdl::Texture	*_texture;
public:
  Ground(const glm::vec2 &pos);
  virtual ~Ground();
  virtual const glm::vec2 &getPos() const;
  virtual void	setPos(const glm::vec2 &new_pos);
  virtual void	update(gdl::Input &input, gdl::Clock const &clock);
  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
};


#endif /* _GROUND_H_ */
