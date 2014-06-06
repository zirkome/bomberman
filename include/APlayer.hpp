#ifndef APLAYER_HPP_
#define APLAYER_HPP_

# include "IEntity.hpp"
# include "Model.hpp"
# include "Map.hpp"
# include "Timer.hpp"

class APlayer : public IEntity
{
  typedef std::list<int> BombList;

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

protected:
  glm::vec2 _pos;
  Model *_obj;
  Map *_map;
  int _speed;
  double _size;
  Way _way;
  Status _status;
  BombList _bombList;
  size_t _stock;
  IEntity::Status _statusOfObject;
  Timer _time;
  int _lvl;

protected:
  APlayer(const glm::vec2 &pos, Map *map);

public:
  virtual ~APlayer();
  void createBomb();

public:
  virtual const glm::vec2 &getPos() const;
  virtual void  setPos(const glm::vec2 &new_pos);
  virtual void  update(gdl::Input &input, gdl::Clock const &clock) = 0;
  virtual void  draw(gdl::AShader *shader, const gdl::Clock& clock);
  virtual IEntity::Type getType() const;
  virtual void  setStatus(APlayer::Status);
  virtual IEntity::Status getStatus() const;
  virtual void setStatus(IEntity::Status status);

protected:
  virtual bool moveUp(double const distance);
  virtual bool moveDown(double const distance);
  virtual bool moveLeft(double const distance);
  virtual bool moveRight(double const distance);
  virtual bool bomb(UNUSED double const distance);
private:
  virtual void updateAnim(bool);
};

#endif
