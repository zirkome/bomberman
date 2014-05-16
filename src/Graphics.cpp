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
  _proj = glm::perspective(_fov, static_cast<float>(win.x) / static_cast<float>(win.y),
                           0.01f, 500.0f);
  _shader = new gdl::BasicShader;

  if (!_shader->load(RES_SHADERS "game.fp", GL_FRAGMENT_SHADER)
      || !_shader->load(RES_SHADERS "game.vp", GL_VERTEX_SHADER)
      || !_shader->build())
    {
      std::cerr << "Load shader fail" << std::endl;
      return false;
    }

  _shader->bind();

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  return true;
}

void GameGraphics::startFrame()
{
  _shader->bind();
  _shader->setUniform("projection", _proj);
}

MenuGraphics::MenuGraphics()
{
}

MenuGraphics::~MenuGraphics()
{

}

bool MenuGraphics::init(const glm::ivec2& win)
{

  _ortho = glm::ortho(0, win.x, win.y, 0, -1, 1);
  _shader = new gdl::BasicShader;

  if (!_shader->load(RES_SHADERS "menu.fp", GL_FRAGMENT_SHADER)
      || !_shader->load(RES_SHADERS "menu.vp", GL_VERTEX_SHADER)
      || !_shader->build())
    {
      std::cerr << "Load shader fail" << std::endl;
      return false;
    }

  _shader->bind();

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  return true;
}

void MenuGraphics::startFrame()
{
  _shader->bind();
  _shader->setUniform("projection", _ortho);
}
