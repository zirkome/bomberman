#include "Graphics.hpp"

GameGraphics::GameGraphics()
{
  _fov = 60.0;
  _fbo = NULL;
}

GameGraphics::~GameGraphics()
{
  delete _fbo;
}

bool GameGraphics::init(const glm::ivec2& win)
{
  _proj = glm::perspective(_fov, static_cast<float>(win.x) / static_cast<float>(win.y),
                           0.1f, 500.0f);
  _fbo = new FBORenderer(win);

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  return true;
}

void GameGraphics::startFrame() const
{
  _fbo->start();
  _fbo->getShader()->setUniform("projection", _proj);
}

void GameGraphics::processFrame(const glm::vec3& camPos) const
{
 _fbo->process(camPos);
}

gdl::AShader *GameGraphics::getShader() const
{
  return _fbo ? _fbo->getShader() : NULL;
}

IntroGraphics::IntroGraphics()
{
  _fov = 60.0;
  _fbo = NULL;
}

IntroGraphics::~IntroGraphics()
{
  if (_fbo != NULL)
    delete _fbo;
}

bool IntroGraphics::init(const glm::ivec2& win)
{
  _proj = glm::perspective(_fov, static_cast<float>(win.x) / static_cast<float>(win.y),
                           0.1f, 500.0f);
  _fbo = new FBORenderer(win);

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

  return true;
}

void IntroGraphics::startFrame() const
{
  _fbo->start();
  _fbo->getShader()->setUniform("projection", _proj);
}

void IntroGraphics::processFrame(const glm::vec3& camPos) const
{
 _fbo->process(camPos);
}

gdl::AShader *IntroGraphics::getShader() const
{
  return _fbo ? _fbo->getShader() : NULL;
}
