#ifndef _GAMEENGINE_HPP_
#define _GAMEENGINE_HPP_

#include <iostream>

#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <IRenderContext.hh>

#include "SoundManager.hpp"
#include "Intro.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include "Map.hpp"

class GameEngine : public gdl::Game
{
public:
  GameEngine();
  virtual ~GameEngine();
  virtual bool initialize();
  virtual bool update();
  virtual void draw();

private:
  enum {
    Intro,
    Game
  } _state;
  bool _init;
  ::Intro *_intro;
  ::Game *_game;
  gdl::Clock _clock;
  gdl::Input _input;
  gdl::IRenderContext *_context;
};

#endif
