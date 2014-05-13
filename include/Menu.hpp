#ifndef MENU_HPP_
#define MENU_HPP_

#include <Clock.hh>
#include "Game.hpp"
#include "Graphics.hpp"

class Menu
{
public:
  Menu();
  ~Menu();
  bool updateMenu(gdl::Input &input, gdl::Clock &clock);
  void drawMenu(const gdl::Clock &clock);

private:
  bool _show;
  Game *_game;
};

#endif
