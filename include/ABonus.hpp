#ifndef _ABONUS_H_
#define _ABONUS_H_

# include <Clock.hh>
# include "config.h"

# include "IEntity.hpp"
# include "Texture.hpp"
# include "SharedPointer.hpp"
# include "ResourceManager.hpp"
# include "Timer.hpp"
# include "GameGeometry.hpp"
# include "APlayer.hpp"

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
protected:
  enum BonusType
    {
      FASTER = 0,
      MULTI_BOMB,
      GHOST,
      BOMB_RANGE
    };

private:
  glm::vec2	_pos;
  GameGeometry	*_obj;
  double	_cube_speed;
  SharedPointer<Texture> _texture;
  std::map<BonusType, std::string> _bonusImg;
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

  virtual void update(APlayer *player, const gdl::Clock &);

  virtual void start(APlayer *player) = 0;
  virtual std::string toString() = 0;

protected:
  virtual void stop(APlayer *player) = 0;
};

#endif /* _ABONUS_H_ */
