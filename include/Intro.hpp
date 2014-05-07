#ifndef INTRO_HPP_
#define INTRO_HPP_

#include "Menu.hpp"

class Intro/* : public gdl::Game*/
{
private:
  bool _show;
  Menu *_menu;
  Graphics _interface;
public:
  Intro();
  ~Intro();
  bool initialize();
  bool update();
  void draw();
};

#endif
