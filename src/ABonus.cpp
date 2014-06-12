# include "ABonus.hpp"

ABonus::ABonus(BonusType type, const glm::vec2 &pos, double effectTime)
  : _pos(pos), _toDisplay(10), _effectTime(effectTime), _type(type)
{
  _status = OK;

  _bonusImg[FASTER] = "bonus_speed_up.tga";
  _bonusImg[MULTI_BOMB] = "bonus_bomb.tga";
  _bonusImg[FLAMME_PASS] = "bonus_flame_pass.tga";
  _bonusImg[BOMB_RANGE] = "bonus_bomb_range.tga";
  _bonusImg[BOMB_PASS] = "bonus_bomb_pass.tga";
  _bonusImg[COIN] = "bonus_coin_texture.tga";

  std::string path = std::string(RES_TEXTURE) + _bonusImg.at(type);
  _texture = ResourceManager::getInstance()->get<Texture>(path);


  _obj = new GameGeometry(ResourceManager::getInstance()->get<AGeometry>("cube.geo"));

  _obj->rotate(glm::vec3(0,1,0), 45.0);
  _obj->rotate(glm::vec3(1,0,0), -45.0);

  _obj->scale(glm::vec3(.25f, .25f, .25f));
  _obj->translate(glm::vec3(pos.x, 0, pos.y));

  _cube_speed = 50.0;
}

ABonus::~ABonus()
{
  delete _obj;
}

const glm::vec2	&ABonus::getPos() const
{
  return _pos;
}

void	ABonus::setPos(const glm::vec2 &new_pos)
{
  _pos = new_pos;
}

void	ABonus::update(UNUSED gdl::Input &input, UNUSED gdl::Clock const &clock)
{
  _obj->rotate(glm::vec3(1,0,1), clock.getElapsed() * _cube_speed);

  if (_toDisplay.update(clock.getElapsed()))
    _status = DESTROY;
}

void	ABonus::update(APlayer *player, const gdl::Clock &clock)
{
  if (_effectTime.update(clock.getElapsed()))
    {
      stop(player);
    }
}

void	ABonus::draw(gdl::AShader *shader, const gdl::Clock& clock) const
{
  _texture->bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  _obj->draw(shader, clock);
}

const std::string ABonus::getTexturePath() const
{
  return std::string(RES_TEXTURE) + _bonusImg.at(_type);
}

IEntity::Type ABonus::getType() const
{
  return IEntity::BONUS;
}

IEntity::Status ABonus::getStatus() const
{
  return _status;
}

void ABonus::setStatus(IEntity::Status status)
{
  _status = status;
}

bool	ABonus::operator==(const ABonus &b)
{
  return _type == b._type;
}
