#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <string>
#include <list>

#include <Input.hh>
#include <Clock.hh>
#include <Texture.hh>
#include "Graphics.hpp"
#include "ArmagetroCam.hpp"
#include "BasicCam.hpp"
#include "Map.hpp"
#include "Ia.hpp"
#include "Player.hpp"
#include "Fault.hpp"
#include "FontText.hpp"
#include "Cube.hpp"
#include "Placement.hpp"
#include "SkyBox.hpp"

class Game
{
public:
  Game(const glm::ivec2& win, const std::string &saveGame);
  Game(const glm::ivec2& win,
       int numberPlayer,
       int numberIA,
       const std::vector<std::string> &algoFileName,
       const std::string &mapName = "");
  ~Game();

public:
  bool updateGame(gdl::Input &input, const gdl::Clock &clock);
  void drawGame(gdl::Input &input, gdl::Clock const &clock);

private:
  void init(const glm::ivec2& win);

  void drawGraphicObject(gdl::AShader *shader, gdl::Clock const &clock) const;

private:
  std::vector<Ia *> _listIA; //Why not Ia and player doesn't hineretaded from the same class ?
  std::vector<Player *> _players; //Those are IEntity
  Map *_currentMap;
  glm::ivec2 _win;
  Cube *_cube;
  ACamera* _cam;
  FontText *_font;
  gdl::Texture	_text_texture;
  GameGraphics _ogl;
  glm::mat4 _ortho;
  Pan *_ground;
  SkyBox _skybox;
};

#endif
