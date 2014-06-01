#ifndef _INTRO_H_
# define _INTRO_H_

# include <Input.hh>
# include <Clock.hh>
# include <Texture.hh>

# include "Model.hpp"
# include "FontText.hpp"
# include "ACamera.hpp"
# include "PivotingCam.hpp"
# include "Graphics.hpp"
# include "Menu.hpp"
# include "Game.hpp"

class Intro
{
public:
  Intro(const glm::ivec2& win);
  virtual ~Intro();

public:
  bool updateIntro(gdl::Input &input, const gdl::Clock &clock);
  void drawIntro(gdl::Clock const &clock) const;
  bool finish() const;
  Game *getGame();
private:
  void init(glm::ivec2 win);

private:
  ::Menu *_menu;
  IntroGraphics _ogl;
  PivotingCam *_cam;
  Model *_player;
  AObject *_logo;
  gdl::Texture *_texture;
  int _speed;
  glm::vec3 _pos;
  glm::vec3 _pos2;
  enum {
    Running,
    Menu,
    Finished
  } _state;
};

#endif /* _INTRO_H_ */
