#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include "Map.hpp"

class Player
{
private:
  int _x;
  int _y;
  Map *_map;

public:
  Player(Map *map);
  ~Player();
};

#endif /* !PLAYER_HPP_ */
