#include <sstream>
#include "Menu.hpp"

Menu::Menu(PivotingCam *cam, IntroGraphics &ogl)
  : _cam(cam), _ogl(ogl), _state(Running), _select(Start)
{
  _font = new FontText(RES_TEXTURE "font.tga");
  init();
}

Menu::~Menu()
{
}

void Menu::init()
{
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
  if (input.getKey(SDLK_UP, true))
    _select = (selected)(_select - 1);
  else if (input.getKey(SDLK_DOWN, true))
    _select = (selected)(_select + 1);
  if (_select < 0)
    _select = Exit;
  if (_select > 2)
    _select = Start;
  /* TODO : move in menu, ... */
  return true;
}

void Menu::drawMenu(UNUSED gdl::Clock const &clock)
{
  gdl::AShader *hudshader = _ogl.getShader();
  glm::mat4 textMat = glm::translate(glm::mat4(1), glm::vec3(0.01f, 0.6f, 0.0f));

  _ogl.startFrame();

  hudshader->bind();
  hudshader->setUniform("view", _ortho);
  hudshader->setUniform("projection", glm::mat4(1));

  textMat = glm::translate(glm::mat4(1), glm::vec3(0.3, 0.59, 0.0));
  textMat = glm::scale(textMat, glm::vec3(1.5, 1.5, 0.0));
  _font->displayText(std::string("Start"), _select == Start ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
  textMat = glm::translate(glm::mat4(1), glm::vec3(0.3, 0.39, 0.0));
  textMat = glm::scale(textMat, glm::vec3(1.5, 1.0, 0.0));
  _font->displayText(std::string("Options"), _select == Options ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
  textMat = glm::translate(glm::mat4(1), glm::vec3(0.3, 0.19, 0.0));
  textMat = glm::scale(textMat, glm::vec3(1.5, 1.0, 0.0));
  _font->displayText(std::string("Exit"), _select == Exit ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
  /* TODO : draw the curent menu */
}
