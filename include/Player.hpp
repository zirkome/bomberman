#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <string>
# include <map>
# include "APlayer.hpp"

class Player : public APlayer
{
  typedef bool (Player::*move)(double const);
  typedef std::map<int, move> MovePtr;

private:
  MovePtr	_movePtr;
public:
  Player(glm::vec2 pos, Map *map);
  ~Player();
  virtual void	update(gdl::Input &input, gdl::Clock const &clock);
};

#endif /* !PLAYER_HPP_ */
