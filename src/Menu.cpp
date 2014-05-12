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

void Menu::drawMenu(Graphics &ogl, gdl::Clock const &clock)
{
  (void) ogl;
  (void) clock;
  /* TODO : draw the curent menu */
}
