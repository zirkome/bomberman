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
  Player(const glm::vec2& pos, Map *map, const glm::vec3& color);
  ~Player();
  virtual void	update(gdl::Input &input, gdl::Clock const &clock);

/* used to determinate if it's the first player or not */
public:
  static int _nb;
};

#endif /* !PLAYER_HPP_ */
