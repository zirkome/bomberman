#ifndef APLAYER_HPP_
#define APLAYER_HPP_

# include "IEntity.hpp"
# include "Model.hpp"
# include "Map.hpp"

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

protected:
  glm::vec2	_vec;
  Model         *_obj;
  Map           *_map;
  int           _speed;
  double        _size;
  Way		_way;
  Status	_status;
  int		_xBomb;
  int		_yBomb;

public:
  virtual ~APlayer();

public:
  virtual const glm::vec2 &getPos() const;
  virtual void  setPos(const glm::vec2 &new_pos);
  virtual void  update(gdl::Input &input, gdl::Clock const &clock) = 0;
  virtual void  draw(gdl::AShader *shader, const gdl::Clock& clock);
  virtual IEntity::Type getType() const;
  virtual void  setStatus(APlayer::Status);

protected:
  virtual bool  moveUp(double const distance);
  virtual bool  moveDown(double const distance);
  virtual bool  moveLeft(double const distance);
  virtual bool  moveRight(double const distance);
  virtual bool	bomb(UNUSED double const distance);
};

#endif
