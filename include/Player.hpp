#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <string>
# include <map>
# include <list>

# include "APlayer.hpp"
# include "Bomb.hpp"

class Player : public APlayer
{
public:
  Player(const glm::vec2& pos, Map *map, bool first, const glm::vec4& color);
  ~Player();
  virtual void	update(gdl::Input &input, gdl::Clock const &clock);
};

#endif /* !PLAYER_HPP_ */
