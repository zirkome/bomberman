#ifndef APLAYER_HPP_
# define APLAYER_HPP_

# include "IEntity.hpp"
# include "Model.hpp"
# include "Map.hpp"
# include "Timer.hpp"

class ABonus;

struct movementCoef
{
  movementCoef(double r, glm::vec2 direction, glm::vec3 trans,
               glm::vec2 distanceLeft, glm::vec2 distanceRight) {
    rotate = r;
    dir = direction;
    translate = trans;
    distLeft = distanceLeft;
    distRight = distanceRight;
  }
  glm::vec2	dir;
  double	rotate;
  glm::vec3	translate;
  glm::vec2	distLeft, distRight;
};

class APlayer : public IEntity
{
public:
  enum Status
  {
    STANDBY = 0,
    WALK,
    STOP_WALK
  };

  enum Way
  {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
  };

  typedef bool (APlayer::*keyAction)();
  typedef std::map<int, keyAction> actionPtr;

protected:
  actionPtr _actionPtr;
  std::vector<int> _moveKey;

  glm::vec2 _pos;
  Map *_map;
  double _speed;
  double _size;
  Way _way;
  Status _status;
  int _stock_bomb, _max_bomb;
  double _bomb_range;
  IEntity::Status _statusOfObject;
  GameModel* _obj;
  int _lvl;
  std::map<int, movementCoef*> _moveConf;
  glm::vec3 _color;
  std::vector<ABonus *>		_bonus;

protected:
  APlayer(const glm::vec2 &pos, Map *map, const glm::vec3& color);

public:
  virtual ~APlayer();

public:
  virtual const glm::vec2 &getPos() const;
  virtual void setPos(const glm::vec2 &new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock) = 0;
  virtual void draw(gdl::AShader *shader, const gdl::Clock& clock) const;
  virtual IEntity::Type getType() const;
  virtual void setStatus(APlayer::Status);
  virtual IEntity::Status getStatus() const;
  virtual void setStatus(IEntity::Status status);
  double       getSpeed() const;
  void	       setSpeed(double newSpeed);
  int	       getStockBomb() const;
  void	       setStockBomb(int);
  int	       getMaxBomb() const;
  void	       setMaxBomb(int);

protected:
  virtual bool	movePlayer(const movementCoef *mcoef, float const distance);
  virtual bool	bomb();
  virtual void	updateAnim(bool hasMoved, bool keyPressed = true);
  void		updateBonus(const gdl::Clock &clock);
};

#endif
