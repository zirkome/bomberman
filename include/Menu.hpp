#ifndef MENU_HPP_
#define MENU_HPP_

#include <Clock.hh>
#include "Game.hpp"
#include "Graphics.hpp"

class Menu
{
public:
  Menu(const glm::ivec2& win);
  ~Menu();
  bool updateMenu(gdl::Input &input, const gdl::Clock &clock);
  void drawMenu(const gdl::Clock &clock);

private:
};

#endif
