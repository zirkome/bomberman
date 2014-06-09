#include "Graphics.hpp"

GameGraphics::GameGraphics()
{
  _init = false;
}

GameGraphics::~GameGraphics()
{
  if (_init)
    {
      delete _font;
      delete _ground;
      delete _shader;
    }
}

bool GameGraphics::init(const glm::ivec2& win, const glm::ivec2& mapSize, bool splitScreen)
{

  _init = true;
  _fov = 60.0;
  _splitScreen = splitScreen;

  _proj = glm::perspective(_fov, (static_cast<float>(win.x) / (_splitScreen + 1))
                           / static_cast<float>(win.y),
                           0.5f, 100.0f);
  _ortho = glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1.0, -1.0, -1.0)), glm::vec3(2.0, 2.0, 2.0));

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

  _win = win;

  glm::ivec2 panSize = mapSize / glm::ivec2(4, 4);
  _ground = new GameGeometry(new Pan(glm::vec2(panSize.x, panSize.y)));

  _ground->scale(glm::vec3(0.5f, 0.5f, 1.0f));
  _ground->translate(glm::vec3(-0.5f, 0, -0.5f));
  _ground->scale(glm::vec3(mapSize.x, mapSize.y, 1.0f));

  _ground->translate(glm::vec3(static_cast<float>(mapSize.x) / 2.0, -0.5f,
                               static_cast<float>(mapSize.y) / 2.0));
  _ground->rotate(glm::vec3(1, 0, 0), 90.0);

  _font = new FontText(RES_TEXTURE "font.tga");
  _groundTex =
    ResourceManager::getInstance()->get<Texture>(
      RES_TEXTURE "ground_texture.tga");
  return true;
}

void GameGraphics::updateGraphic(gdl::Clock const &clock)
{
  _skybox.update(clock);
}


void GameGraphics::drawGame(gdl::Clock const& clock, const std::vector<PlayerManager*>& players) const
{
  int i = 0;
  for (std::vector<PlayerManager*>::const_iterator it = players.begin(), end = players.end();
       it != end; ++it)
    {
      ACamera& cam = (*it)->getCam();

      _shader->setUniform("lightDir", glm::vec3(0.0f, 0.0f, 0.0f));
      _shader->setUniform("camPos", cam.getPosition());
      _shader->setUniform("view", cam.project());
      _shader->setUniform("projection", _proj);

      glEnable(GL_CULL_FACE);

      if (_splitScreen)
        glViewport((_win.x / 2) * i, 0, _win.x / 2, _win.y);

      glDisable(GL_DEPTH_TEST);
      _skybox.draw(_shader, clock, cam.getPosition());
      glEnable(GL_DEPTH_TEST);

      _shader->setUniform("lightDir", glm::vec3(0.1, 0.6, -0.3));

      const std::list<IEntity*>& ent = (*it)->getNearList();

      for (std::list<IEntity*>::const_iterator itt = ent.begin(), end = ent.end(); itt != end; ++itt)
        if ((*itt)->getStatus() != IEntity::DESTROY)
          (*itt)->draw(_shader, clock);

      glDisable(GL_CULL_FACE);

      _groundTex->bind();
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      _ground->draw(_shader, clock);
      ++i;
    }
  if (_splitScreen)
    glViewport(0, 0, _win.x, _win.y);
}

void GameGraphics::setHudProj() const
{
  glEnable(GL_CULL_FACE);

  _shader->setUniform("lightDir", glm::vec3(0.0f, 0.0f, 0.0f));
  _shader->setUniform("view", _ortho);
  _shader->setUniform("projection", glm::mat4(1));
}

gdl::AShader *GameGraphics::getShader() const
{
  return _shader;
}

const FontText& GameGraphics::getTextWriter() const
{
  return *_font;
}
