#include "PivotingCam.hpp"
#include "Intro.hpp"

Intro::Intro(const glm::ivec2& win)
  : _speed(4), _pos(25.0, 0.0f, 0.0), _state(Running)
{
  _player = new Model(RES_MODEL "marvin.fbx");
  _player->initialize();
  _player->translate(glm::vec3(20.0, -0.5f, 0.0));
  _player->rotate(glm::vec3(0, 1, 0), -90.0);
  _player->scale(glm::vec3(0.003, 0.003, 0.003));
  _player->createSubAnim(0, "standby", 0, 0);
  _player->createSubAnim(0, "start_walking", 0, 41);
  _player->createSubAnim(0, "walk", 42, 63);
  _player->createSubAnim(0, "stop_walking", 64, 121);
  _player->setCurrentSubAnim("walk");

  _logo = new Pan();
  _logo->initialize();
  _logo->translate(_pos);
  _logo->scale(glm::vec3(2.0f, 3.0f, 2.0f));
  _logo->rotate(glm::vec3(0, 0, 1), 90.0);
  _texture = AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::LOGO);

  init(win);
}

Intro::~Intro()
{
}

void Intro::init(glm::ivec2 win)
{
  //_cam = new TrackCam(_pos);
  _cam = new PivotingCam(glm::vec2(_pos.x, _pos.y), -0.5, 10);
  _ogl.init(win);
}

bool Intro::updateIntro(gdl::Input &input, const gdl::Clock &clock)
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
	_state = Finished;
    }
  else if (_pos.y < 4.0)
    {
      _pos.y += clock.getElapsed();
      _logo->translate(glm::vec3(0, clock.getElapsed(), 0));
    }
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
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  _logo->draw(shader, clock);
  glDisable(GL_BLEND);

  _ogl.processFrame(_cam->getPosition());
}
