#include "PivotingCam.hpp"
#include "Intro.hpp"

Intro::Intro(const glm::ivec2& win, UNUSED bool menu)
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
  /*  if (menu)
    {
      _state = Menu;
      _menu = new ::Menu(_cam);
      }*/
}

Intro::~Intro()
{
  if (_menu != NULL)
    delete _menu;
}

void Intro::init(const glm::ivec2& win)
{
  _cam = new PivotingCam(glm::vec2(_pos.x, _pos.y), -0.5, 10);

  _shader = new BasicShader();

  _proj = glm::perspective(60.0f, static_cast<float>(win.x) / static_cast<float>(win.y),
                           0.1f, 500.0f);

  if (!_shader->load(RES_SHADERS "menu.fp", GL_FRAGMENT_SHADER)
      || !_shader->load(RES_SHADERS "menu.vp", GL_VERTEX_SHADER)
      || !_shader->build())
    {
      throw std::runtime_error("Load shader fail");
    }

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

  glEnable(GL_CULL_FACE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
          _menu = new ::Menu(_cam);
        }
    }
  else if (_state == Menu)
    {
      if (_menu->finish())
	_state = Finished;
      if (_pos.y < 4.0)
        {
          _pos.y += clock.getElapsed() * _speed;
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
  _shader->bind();
  _shader->setUniform("view", _cam->project());
  _shader->setUniform("projection", _proj);

  _player->draw(_shader, clock);

  _texture->bind();
  _logo->draw(_shader, clock);

  if (_state == Menu)
    _menu->drawMenu(clock, _shader);

}
