#include "Menu.hpp"

Menu::Menu()
{
  _show = true;
}

Menu::~Menu()
{
}

bool Menu::updateMenu(gdl::Input &input)
{
  (void) input;
  /* TODO : move in menu, ... */
  return true;
}

void Menu::drawMenu(Graphics &ogl)
{
  (void) ogl;
  /* TODO : draw the curent menu */
}
