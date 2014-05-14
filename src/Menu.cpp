#include "Menu.hpp"

Menu::Menu(const glm::ivec2& win)
{
  _show = true;

  _ogl.init(win);
}

Menu::~Menu()
{
}

bool Menu::updateMenu(gdl::Input &input, gdl::Clock &clock)
{
  (void) input;
  (void) clock;
  /* TODO : move in menu, ... */
  return true;
}

void Menu::drawMenu(gdl::Clock const &clock)
{
  (void) clock;
  /* TODO : draw the curent menu */
}
