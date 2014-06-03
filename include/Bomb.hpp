#ifndef BOMB_HPP_
# define BOMB_HPP_

# include <Texture.hh>
# include <AssetsManager.hpp>
# include "Map.hpp"
# include "Cube.hpp"
# include "config.h"
# include "Model.hpp"
# include "Timer.hpp"
# include "Fire.hpp"

class Bomb : public IEntity
{
  typedef std::list<Fire *> FireList;

private:
  glm::vec2	_vec;
  Model *_obj;
  int _lvl;
  Map *_map;
  FireList _fireList;
  Timer _time;
  float _range;
  IEntity::Status _status;
  int _speed;
  double _distance;

public:
  Bomb(const glm::vec2 &pos, int lvl, Map *map);
  virtual ~Bomb();
  virtual const glm::vec2 &getPos() const;
  virtual void	setPos(const glm::vec2 &new_pos);
  virtual void	update(gdl::Input &input, gdl::Clock const &clock);
  virtual void  draw(gdl::AShader *shader, const gdl::Clock& clock);
  virtual IEntity::Type getType() const;
  virtual IEntity::Status getStatus() const;
  virtual void setStatus(IEntity::Status status);

private:
  void	explode(gdl::Clock const &clock);
  bool	destroyEntity(int x, int y) const;
  void	spreadTop(double distance);
  void	spreadLeft();
  void	spreadDown();
  void	spreadRight();
};

#endif /* !BOMB_HPP_ */
