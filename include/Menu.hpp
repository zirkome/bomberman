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
  Menu(const glm::ivec2& win);
  ~Menu();
  bool updateMenu(gdl::Input &input, const gdl::Clock &clock);
  void drawMenu(const gdl::Clock &clock);
  bool finish() const;
  void init(const glm::ivec2& win);
private:
  PivotingCam *_cam;
  IntroGraphics _ogl;
  FontText *_font;
  glm::vec3 _pos;
  glm::mat4 _ortho;
  enum {
    Running,
    Finished
  } _state;
};

#endif
