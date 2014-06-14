#ifndef FIREBALL_HPP_
# define FIREBALL_HPP_

# include "SharedPointer.hpp"
# include "Texture.hpp"
# include "Map.hpp"
# include "APlayer.hpp"
# include "GameGeometry.hpp"
# include "ResourceManager.hpp"
# include "BonusFactory.hpp"

class FireBall : public IEntity
{
public:
  FireBall(const glm::vec2 &pos, const movementCoef *mcoef, Map *map, APlayer *player);
  virtual ~FireBall();
  virtual const glm::vec2 &getPos() const;
  virtual void	setPos(const glm::vec2 &new_pos);
  virtual void update(gdl::Input &input, gdl::Clock const &clock);
  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock) const;
  virtual IEntity::Type getType() const;
  virtual IEntity::Status getStatus() const;
  virtual void setStatus(IEntity::Status status);

private:
  void	destroyEntity(IEntity *entity);

private:
  GameGeometry* _obj;
  IEntity::Status _status;
  SharedPointer<Texture> _texture;
  glm::vec2 _pos;
  const movementCoef *_mcoef;
  Map *_map;
  double _speed;
  APlayer *_player;
};

#endif /* !FIREBALL_HPP_ */
