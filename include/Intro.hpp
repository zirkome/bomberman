#ifndef INTRO_HPP_
#define INTRO_HPP_

#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include <Model.hh>

#include "Menu.hpp"

class Intro : public gdl::Game
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
