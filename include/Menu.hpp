#ifndef MENU_HPP_
#define MENU_HPP_

#include <Clock.hh>
#include "Game.hpp"
#include "Graphics.hpp"

class Menu
{
private:
  bool _show;
  Game *_game;
public:
  Menu();
  ~Menu();
  bool updateMenu(gdl::Input &input, gdl::Clock &clock);
  void drawMenu(Graphics &ogl, gdl::Clock const &clock);
};

#endif
