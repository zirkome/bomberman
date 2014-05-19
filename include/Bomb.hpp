#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "Cube.hpp"
# include "IEntity.hpp"

class Bomb : public IEntity
{
private:
  glm::vec2	_vec;
  AObject *_obj;

public:
  Bomb(glm::vec2 pos);
  virtual ~Bomb();
  virtual glm::vec2	getPos() const;
  virtual void	setPos(glm::vec2 new_pos);
  virtual void	update(gdl::Input &input, gdl::Clock const &clock);
  virtual void  draw(gdl::AShader *shader, const gdl::Clock& clock);
};

#endif /* !BOMB_HPP_ */
