#ifndef APLAYER_HPP_
# define APLAYER_HPP_

# include <boost/archive/binary_oarchive.hpp>
# include <boost/archive/binary_iarchive.hpp>
# include <boost/serialization/base_object.hpp>

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
  friend class boost::serialization::access;

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
  SharedPointer<Texture> _colorTexture;
  SharedPointer<Texture> _defaultColorTexture;
  int _lvl;
  bool _flammePass, _bombPass;
  std::map<int, movementCoef*> _moveConf;
  glm::vec4 _color;
  std::vector<ABonus *>		_bonus;
  std::string _name;
  int _scores;

public:
  template<class Archive>
  void serialize(Archive & ar, UNUSED const unsigned int version)
  {
    ar & _pos.x;
    ar & _pos.y;
    ar & _speed;
    ar & _size;
    ar & _stock_bomb;
    ar & _max_bomb;
    ar & _bomb_range;
    ar & _flammePass;
    ar & _bombPass;
    ar & _lvl;
  }

protected:
  APlayer(const glm::vec2 &pos, Map *map, const glm::vec4& color, const std::string &name);

public:
  virtual ~APlayer();

public:
  virtual const glm::vec2 &getPos() const;
  virtual void setPos(const glm::vec2 &new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock) = 0;
  virtual void draw(gdl::AShader *shader, const gdl::Clock& clock) const;
  virtual void addBonus(ABonus *);
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
  double       getBombRange() const;
  void	       setBombRange(double);
  void	       setBombPass(bool);
  bool	       getBombPass() const;
  void	       setFlammePass(bool);
  bool	       getFlammePass() const;
  void	       increaseScores(int number);
  int	       getScores() const;
  std::string  getName() const;
  const std::vector<ABonus *>& getBonus() const;

protected:
  virtual bool	movePlayer(const movementCoef *mcoef, float const distance);
  virtual bool	bomb();
  virtual void	updateAnim(bool hasMoved, bool keyPressed = true);
  void		updateBonus(const gdl::Clock &clock);
};

#endif
