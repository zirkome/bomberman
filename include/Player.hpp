#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <string>
# include <map>
# include <list>
# include "APlayer.hpp"
# include "AssetsManager.hpp"
# include "Bomb.hpp"

class Player : public APlayer
{
  typedef bool (Player::*move)(double const);
  typedef std::map<int, move> MovePtr;
  typedef std::list<int> BombList;

private:
  MovePtr	_movePtr;
  BombList	_bombList;

public:
  Player(glm::vec2 pos, Map *map);
  ~Player();
  virtual void	update(gdl::Input &input, gdl::Clock const &clock);
private:
  bool putBomb(UNUSED double const distance);
};

#endif /* !PLAYER_HPP_ */
