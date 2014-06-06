#include "Graphics.hpp"

GameGraphics::GameGraphics(bool splitScreen)
{
  _fov = 60.0;
  _splitScreen = splitScreen;
}

GameGraphics::~GameGraphics()
{
}

bool GameGraphics::init(const glm::ivec2& win)
{
  _proj = glm::perspective(_fov, (static_cast<float>(win.x) / (_splitScreen + 1))
                           / static_cast<float>(win.y),
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
