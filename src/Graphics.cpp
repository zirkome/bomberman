#include "Graphics.hpp"

GameGraphics::GameGraphics()
{
  _fov = 60.0;
}

GameGraphics::~GameGraphics()
{
}

bool GameGraphics::init(const glm::ivec2& win)
{
  _proj = glm::perspective(_fov, (static_cast<float>(win.x) / 2.0f) / static_cast<float>(win.y),
                           0.5f, 100.0f);

  _shader = new BasicShader();

  if (!_shader->load(RES_SHADERS "game.fp", GL_FRAGMENT_SHADER)
      || !_shader->load(RES_SHADERS "game.vp", GL_VERTEX_SHADER)
      || !_shader->build())
    {
      throw std::runtime_error("Load shader fail");
    }

  _shader->bind();
  _shader->setUniform("projection", _proj);
  _shader->setUniform("ambientLight", glm::vec4(0.005, 0.005, 0.005, 1.0));

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  return true;
}


gdl::AShader *GameGraphics::getShader() const
{
  return _shader;
}

const glm::mat4 &GameGraphics::getPerspectiveProj() const
{
  return _proj;
}

IntroGraphics::IntroGraphics()
{
  _fov = 60.0;
}

IntroGraphics::~IntroGraphics()
{
}

bool IntroGraphics::init(const glm::ivec2& win)
{
  _proj = glm::perspective(_fov, static_cast<float>(win.x) / static_cast<float>(win.y),
                           0.1f, 500.0f);

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

  glEnable(GL_CULL_FACE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _hudShader = new BasicShader();

  if (!_hudShader->load(RES_SHADERS "menu.fp", GL_FRAGMENT_SHADER)
      || !_hudShader->load(RES_SHADERS "menu.vp", GL_VERTEX_SHADER)
      || !_hudShader->build())
    {
      throw std::runtime_error("Load shader fail");
    }

  _hudShader->bind();
  _hudShader->setUniform("projection", _proj);

  return true;
}

void IntroGraphics::startFrame() const
{
  _hudShader->setUniform("projection", _proj);
}

gdl::AShader *IntroGraphics::getShader() const
{
  return _hudShader;
}
