#include "Menu.hpp"

Menu::Menu()
{
  _show = true;
}

Menu::~Menu()
{
}

bool Menu::updateMenu(Graphics &interface)
{
  if (!_show)
    return _game->updateGame(interface);
  /* TODO : move in menu, ... */
  return true;
}

void Menu::drawMenu(Graphics &interface)
{
  if (!_show)
    return _game->drawGame(interface);
  /* TODO : draw the curent menu */
}
