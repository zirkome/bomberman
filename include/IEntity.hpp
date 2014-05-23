#ifndef IENTITY_HPP_
#define IENTITY_HPP_

# include <Clock.hh>
# include <Input.hh>
# include <AShader.hh>

class	AObject;

class IEntity
{
public:
  enum Type
    {
      BOX = 0,
      WALL,
      BOMB,
      GROUND,
      MODEL,
      PLAYER,
      LOGO,
      NONE
    };
  enum Symbol
    {
      S_BOX = 'o',
      S_WALL = '#'
    };

  virtual ~IEntity() {}
  virtual const glm::vec2 &getPos() const = 0;
  virtual void setPos(const glm::vec2 &new_pos) = 0;
  virtual void update(gdl::Input &input, gdl::Clock const &clock) = 0;
  virtual void draw(gdl::AShader *shader, const gdl::Clock& clock) = 0;
  virtual IEntity::Type getType() const = 0;
};

#endif
