#ifndef MENU_HPP_
#define MENU_HPP_

#include <Clock.hh>
#include "Game.hpp"
#include "Graphics.hpp"
#include "ACamera.hpp"
#include "PivotingCam.hpp"
#include "Graphics.hpp"

class Menu
{
public:
  Menu(PivotingCam *cam, IntroGraphics &ogl);
  ~Menu();
  bool updateMenu(gdl::Input &input, const gdl::Clock &clock);
  void drawMenu(const gdl::Clock &clock);
  Game *getGame();
  bool finish() const;
private:
  void init();
private:
  int _numberPlayer;
  int _numberIa;
  std::vector<std::string> _iaFile;
  std::string _mapFile;
  Game *_game;
  PivotingCam *_cam;
  IntroGraphics &_ogl;
  FontText *_font;
  glm::vec3 _pos;
  glm::mat4 _ortho;
  enum {
    Running,
    Finished
  } _state;
  enum selected {
    Start = 0,
    Options,
    Exit
  } _select;
};

#endif
