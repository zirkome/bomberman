#ifndef _INTRO_H_
# define _INTRO_H_

# include <Input.hh>
# include <Clock.hh>

# include "SharedPointer.hpp"
# include "Texture.hpp"
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
  Intro(const glm::ivec2& win, bool menu = false);
  virtual ~Intro();

public:
  bool updateIntro(gdl::Input &input, const gdl::Clock &clock);
  void drawIntro(gdl::Clock const &clock) const;
  bool finish() const;
  Game *getGame();
private:
  void init(const glm::ivec2& win);

private:
  ::Menu *_menu;
  PivotingCam *_cam;
  AObject *_logo;
  glm::mat4 _proj;
  SharedPointer<Texture> _texture;
  gdl::AShader *_shader;
  int _speed;
  glm::vec3 _pos;
  glm::vec3 _pos2;
  enum {
    Running,
    Menu,
    Finished
  } _state;
  GameModel* _bomb;
  GameModel* _player;
};

#endif /* _INTRO_H_ */
