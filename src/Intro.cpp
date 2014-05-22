#include "FreeCam.hpp"
#include "Intro.hpp"

Intro::Intro(const glm::ivec2& win)
  : _speed(4)
{
  _obj = new Model(RES_ASSETS "marvin.fbx");
  _obj->initialize();
  _obj->translate(glm::vec3(10.0, 0.0, 0.0));
  _obj->rotate(glm::vec3(0, 1, 0), -90);
  _obj->scale(glm::vec3(0.003, 0.003, 0.003));
  _obj->createSubAnim(0, "standby", 0, 0);
  _obj->createSubAnim(0, "start_walking", 0, 41);
  _obj->createSubAnim(0, "walk", 42, 63);
  _obj->createSubAnim(0, "stop_walking", 64, 121);
  _obj->setCurrentSubAnim("walk");
  init(win);
}

Intro::~Intro()
{
}

void Intro::init(glm::ivec2 win)
{
  _cam = new FreeCam;
  _ogl.init(win);
}

bool Intro::updateIntro(gdl::Input &input, const gdl::Clock &clock)
{
  _cam->update(input, clock);
  _obj->translate(glm::vec3(-(clock.getElapsed() * _speed), 0, 0));

  return true;
}

void Intro::drawIntro(gdl::Clock const &clock) const
{
  gdl::AShader *shader = _ogl.getShader();

  _ogl.startFrame();
  shader->setUniform("view", _cam->project());

  _obj->draw(shader, clock);

  _ogl.processFrame(_cam->getPosition());
}
