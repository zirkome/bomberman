#ifndef INTRO_HPP_
#define INTRO_HPP_

#include <Game.hh>

#include "Menu.hpp"

class Intro : public gdl::Game
{
public:
  Intro();
  ~Intro();
  virtual bool initialize();
  virtual bool update();
  virtual void draw();

private:
  bool _show;
  Menu *_menu;
  Graphics _ogl;
  gdl::Clock _clock;
  gdl::Input _input;
};

#endif
