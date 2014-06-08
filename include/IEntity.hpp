#ifndef IENTITY_HPP_
# define IENTITY_HPP_

# include <Clock.hh>
# include <Input.hh>
# include <AShader.hh>

class IEntity
{
public:
  enum Type
  {
    BOX = 0,
    WALL,
    BOMB,
    GROUND,
    FIRE,
    MODEL,
    PLAYER,
    SKYBOX,
    LOGO,
    NONE
  };
  enum Symbol
  {
    S_BOX = 'o',
    S_WALL = '#',
    S_NONE = ' '
  };
  enum Status
  {
    OK = 0,
    BURNING,
    DESTROY
  };

  virtual ~IEntity() {}
  virtual const glm::vec2 &getPos() const = 0;
  virtual void setPos(const glm::vec2 &new_pos) = 0;
  virtual void update(gdl::Input &input, gdl::Clock const &clock) = 0;
  virtual void draw(gdl::AShader *shader, const gdl::Clock& clock) const = 0;
  virtual IEntity::Type getType() const = 0;
  virtual IEntity::Status getStatus() const = 0;
  virtual void setStatus(IEntity::Status status) = 0;
};

#endif
