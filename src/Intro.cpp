#include "PivotingCam.hpp"
#include "Intro.hpp"

Intro::Intro(const glm::ivec2& win)
  : _speed(4), _pos(25.0, 0.0f, 0.0), _pos2(25.0, 0.0f, 0.0f), _state(Running)
{
  _menu = NULL;

  _player = new Model(RES_MODEL "marvin.fbx");
  _player->translate(glm::vec3(20.0, -0.5f, 0.0));
  _player->rotate(glm::vec3(0, 1, 0), -90.0);
  _player->scale(glm::vec3(0.003, 0.003, 0.003));
  _player->createSubAnim(0, "standby", 0, 0);
  _player->createSubAnim(0, "start_walking", 0, 41);
  _player->createSubAnim(0, "walk", 42, 63);
  _player->createSubAnim(0, "stop_walking", 64, 121);
  _player->setCurrentSubAnim("walk");

  _logo = new Pan();
  _logo->translate(_pos);
  _logo->scale(glm::vec3(5.0f, 1.0f, 2.0f));
  _logo->rotate(glm::vec3(1, 0, 0), 180.0);
  _texture = AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::LOGO);

  init(win);
}

Intro::~Intro()
{
  if (_menu != NULL)
    delete _menu;
}

void Intro::init(glm::ivec2 win)
{
  //_cam = new TrackCam(_pos);
  _cam = new PivotingCam(glm::vec2(_pos.x, _pos.y), -0.5, 10);
  _ogl.init(win);
}

Game *Intro::getGame()
{
  return _menu->getGame();
}

bool Intro::finish() const
{
  if (_state == Finished)
    return true;
  return false;
}

bool Intro::updateIntro(UNUSED gdl::Input &input, const gdl::Clock &clock)
{
  _cam->update(glm::vec2(_pos.x, _pos.y));
  if (_state == Running)
    {
      if (_pos.x > 0.0)
        {
          _pos.x += -(clock.getElapsed() * _speed);
          _logo->translate(glm::vec3(-(clock.getElapsed() * _speed), 0, 0));
        }
      else
	{
	  //          _logo->translate(glm::vec3(0, 5, 0));
	  _state = Menu;
	  _menu = new ::Menu(_cam, _ogl);
	}
    }
  else if (_state == Menu)
    {
      if (_menu->finish())
	_state = Finished;
      if (_pos.y < 4.0)
	{
	  _pos.y += clock.getElapsed()*_speed;
	  _logo->translate(glm::vec3(0, clock.getElapsed()*_speed, 0));
	}
      if (_pos2.y > 27.5)
	{
	  _player->translate(glm::vec3(_pos2.y, 0, 0));
	  _pos2.y = 0.0;
	}
      else
	{
      _pos2.y += clock.getElapsed() * _speed;
      _player->translate(glm::vec3(-(clock.getElapsed() * _speed), 0, 0));
	}
      return _menu->updateMenu(input, clock);
    }
  _pos2.y += clock.getElapsed() * _speed;
  _player->translate(glm::vec3(-(clock.getElapsed() * _speed), 0, 0));
  return true;
}

void Intro::drawIntro(gdl::Clock const &clock) const
{
  gdl::Texture texture;
  gdl::AShader *shader = _ogl.getShader();

  _ogl.startFrame();
  shader->setUniform("view", _cam->project());

  _player->draw(shader, clock);

  _texture->bind();
  _logo->draw(shader, clock);

  if (_state == Menu)
    _menu->drawMenu(clock);

}
