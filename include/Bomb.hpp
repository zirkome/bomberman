#ifndef BOMB_HPP_
# define BOMB_HPP_

# include <Texture.hh>
# include <stdlib.h>

# include "Map.hpp"
# include "Cube.hpp"
# include "config.h"
# include "Model.hpp"
# include "Timer.hpp"
# include "Fire.hpp"
# include "APlayer.hpp"
# include "SoundManager.hpp"
# include "SharedPointer.hpp"
# include "ResourceManager.hpp"

#include "BonusFactory.hpp"

class Bomb : public IEntity
{
  typedef std::list<Fire *> FireList;

private:
  APlayer *_player;
  glm::vec2 _vec;
  Map *_map;
  FireList _fireList;
  Timer _time;
  Timer _staytime;
  double _range;
  GameModel *_obj;
  IEntity::Status _status;
  int _speed;
  double _distance;

  std::vector<ABonus *> _generatedBonus;
public:
  Bomb(APlayer *player, const glm::vec2 &pos, int range, Map *map);
  virtual ~Bomb();
  virtual const glm::vec2 &getPos() const;
  virtual void	setPos(const glm::vec2 &new_pos);
  virtual void	update(gdl::Input &input, gdl::Clock const &clock);
  virtual void draw(gdl::AShader *shader, const gdl::Clock& clock) const;
  virtual IEntity::Type getType() const;
  virtual IEntity::Status getStatus() const;
  virtual void setStatus(IEntity::Status status);
private:

  void	explode(gdl::Clock const &clock);
  char	destroyEntity(const glm::vec2 &, bool destroy);
  bool	spreadTop(bool destroy);
  bool	spreadLeft(bool destroy);
  bool	spreadDown(bool destroy);
  bool	spreadRight(bool destroy);
};

#endif /* !BOMB_HPP_ */
