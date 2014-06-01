#include <sstream>
#include "Menu.hpp"

Menu::Menu(const glm::ivec2& win)
  : _pos(25.0, 0.0f, 0.0),  _state(Running)
{
  _font = new FontText(RES_TEXTURE "font.tga");
  init(win);
}

Menu::~Menu()
{
}

void Menu::init(const glm::ivec2& win)
{
  _cam = new PivotingCam(glm::vec2(_pos.x, _pos.y), -0.5, 10);
  _ogl.init(win);
  _ortho = glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1.0, -1.0, -1.0)), glm::vec3(2.0, 2.0, 2.0));
}

bool Menu::finish() const
{
  if (_state == Finished)
    return true;
  return false;
}

bool Menu::updateMenu(UNUSED gdl::Input &input, UNUSED const gdl::Clock &clock)
{
  /* TODO : move in menu, ... */
  return true;
}

void Menu::drawMenu(UNUSED gdl::Clock const &clock)
{
  std::stringstream ss;
  gdl::AShader *hudshader = _ogl.getShader();
  glm::mat4 textMat = glm::translate(glm::mat4(1), glm::vec3(0.01f, 0.6f, 0.0f));

  _ogl.startFrame();

  hudshader->bind();
  hudshader->setUniform("view", _ortho);
  hudshader->setUniform("projection", glm::mat4(1));

  ss << "Menu";
  textMat = glm::translate(glm::mat4(1), glm::vec3(0.8, 0.97, 0.0));
  textMat = glm::scale(textMat, glm::vec3(0.5, 0.5, 0.0));
  _font->displayText(ss.str(), 1 ? glm::vec4(0.0f, 1.0f, 0.0f, 0.8f) : glm::vec4(1.0f, 0.0f, 0.0f, 0.8f), textMat, hudshader);
  /* TODO : draw the curent menu */
}
