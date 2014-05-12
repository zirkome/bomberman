#ifndef INTRO_HPP_
#define INTRO_HPP_

#include <iostream>

#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <IRenderContext.hh>

#include "Menu.hpp"
#include "Game.hpp"

class GameEngine : public gdl::Game
{
public:
  GameEngine();
  virtual ~GameEngine();
  virtual bool initialize();
  virtual bool update();
  virtual void draw();

private:
  bool _show;
  bool _init;
  Menu *_menu;
  ::Game *_game;
  Graphics _ogl;
  gdl::Clock _clock;
  gdl::Input _input;
  gdl::IRenderContext *_context;
};

#endif
