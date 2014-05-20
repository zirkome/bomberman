#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <map>
# include "Model.hpp"
# include "IEntity.hpp"
# include "Map.hpp"

class Player : public IEntity
{
  typedef bool (Player::*move)(double const);
  typedef std::map<int, move> MovePtr;

private:
  glm::vec2	_vec;
  AObject	*_obj;
  Map		*_map;
  int		_speed;
  MovePtr	_movePtr;
public:
  Player(glm::vec2 pos, Map *map);
  ~Player();
  virtual const glm::vec2 &getPos() const;
  virtual void	setPos(const glm::vec2 &new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
  virtual IEntity::Type getType() const;
private:
  bool	moveUp(double const distance);
  bool	moveDown(double const distance);
  bool	moveLeft(double const distance);
  bool	moveRight(double const distance);
};

#endif /* !PLAYER_HPP_ */
