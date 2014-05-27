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
                           0.5f, 100.0f);
  _fbo = new FBORenderer(win);

  _hudShader = new BasicShader();

  if (!_hudShader->load(RES_SHADERS "menu.fp", GL_FRAGMENT_SHADER)
      || !_hudShader->load(RES_SHADERS "menu.vp", GL_VERTEX_SHADER)
      || !_hudShader->build())
    {
      throw std::runtime_error("Load shader fail");
    }

  _hudShader->bind();
  _hudShader->setUniform("projection", _proj);
  getShader()->bind();
  getShader()->setUniform("projection", _proj);

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return true;
}

void GameGraphics::startFrame() const
{
  _fbo->start();
}

void GameGraphics::processFrame(const glm::vec3& camPos) const
{
  _fbo->process(camPos);
}

gdl::AShader *GameGraphics::getShader() const
{
  return _fbo ? _fbo->getShader() : NULL;
}

gdl::AShader *GameGraphics::getHudShader() const
{
  return _hudShader;
}
