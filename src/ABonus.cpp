# include "ABonus.hpp"

ABonus::ABonus(BonusType type, const glm::vec2 &pos, double effectTime)
  : _pos(pos), _toDisplay(10), _effectTime(effectTime)
{
  _status = OK;

  // _typeConf[SLOWLY] = new bonusConf(glm::vec4(1,0,0,1), 10);
  _bonusImg[FASTER] = "bonus_speed_up.tga";
  _bonusImg[SLOWLY] = "bonus_speed_down.tga";

  std::string path = std::string(RES_TEXTURE) + _bonusImg[type];
  _texture = ResourceManager::getInstance()->get<Texture>(path);
  _obj = new Cube;


  _obj->rotate(glm::vec3(0,1,0), 45.0);
  _obj->rotate(glm::vec3(1,0,0), -20.0);

  _obj->scale(glm::vec3(.25f, .25f, .25f));
  _obj->translate(glm::vec3(pos.x, 0, pos.y));

  _cube_speed = 50.0;
}

ABonus::~ABonus()
{
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
  _obj->rotate(glm::vec3(0,1,0), clock.getElapsed() * _cube_speed);

  if (_toDisplay.update(clock.getElapsed()))
    _status = DESTROY;
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

// BonusType	ABonus::getRandomBonus()
// {
//   std::vector<int>	vecType;
//   BonusType	bonus;

//   vecType.push_back(FASTER);
//   vecType.push_back(SLOWLY);
//   // vecType.push_back(GHOST);
//   // vecType.push_back(MULTI_BOMB);
//   // vecType.push_back(LOSE_ALL);
//   // vecType.push_back(BOMB_RANGE);

//   bonus = rand() % vecType.size();

//   return bonus;
// }
