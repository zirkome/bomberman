#include "Menu.hpp"

Menu::Menu()
{
  _show = true;
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

void Menu::drawMenu(Graphics &ogl)
{
  (void) ogl;
  /* TODO : draw the curent menu */
}
