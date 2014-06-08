#ifndef _ABONUS_H_
#define _ABONUS_H_

# include <Clock.hh>
# include "config.h"

# include "Texture.hpp"
# include "SharedPointer.hpp"
# include "ResourceManager.hpp"
# include "APlayer.hpp"
# include "Timer.hpp"

struct bonusConf
{
  bonusConf(const glm::vec4 &color, int time) {
    _time = time;
    _color = color;
  }
  int		_time;
  glm::vec4	_color;
};

class ABonus : public IEntity
{
public:
  enum BonusType
    {
      FASTER = 0,
      SLOWLY,
      GHOST,
      MULTI_BOMB,
      LOSE_ALL,
      BOMB_RANGE
    };

private:
  glm::vec2	_pos;
  AObject	*_obj;
  double	_cube_speed;
  std::map<int, bonusConf *>	_typeConf;
  SharedPointer<Texture> _texture;
protected:
  IEntity::Status _status;
  Timer		_toDisplay, _effectTime;

public:
  ABonus(BonusType type, const glm::vec2 &pos, double effectTime);
  virtual ~ABonus();
  virtual const glm::vec2 &getPos() const;
  virtual void setPos(const glm::vec2 &new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual void draw(gdl::AShader *shader, const gdl::Clock& clock) const;
  virtual IEntity::Type getType() const;
  virtual IEntity::Status getStatus() const;
  virtual void setStatus(IEntity::Status status);

  virtual void start(APlayer *player) = 0;
  virtual void update(APlayer *player, const gdl::Clock &) = 0;
  virtual std::string toString() = 0;

protected:
  virtual void stop(APlayer *player) = 0;
// private:
//   BonusType getRandomBonus() const;
};

#endif /* _ABONUS_H_ */
