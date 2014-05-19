#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include "Model.hpp"
# include "IEntity.hpp"
# include "Map.hpp"

class Player : public IEntity
{
private:
  glm::vec2	_vec;
  AObject	*_obj;
public:
  Player(glm::vec2 pos);
  ~Player();
  virtual const glm::vec2 &getPos() const;
  virtual void	setPos(const glm::vec2 &new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
};

#endif /* !PLAYER_HPP_ */
