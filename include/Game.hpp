#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <string>

#include <Input.hh>
#include <Clock.hh>
#include <Texture.hh>
#include "Graphics.hpp"
#include "Map.hpp"
#include "Ia.hpp"
#include "Player.hpp"
#include "Fault.hpp"
#include "FontText.hpp"
#include "Cube.hpp"

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
  void drawGame(gdl::Clock const &clock);

private:
  void init(glm::ivec2 win);

private:
  std::vector<Ia *> _listIA; //Why not Ia and player doesn't hineretaded from the same class ?
  std::vector<Player *> _players; //Those are IEntity
  Map *_currentMap;
  Cube *_cube;
  ACamera* _cam;
  bool updateGame(gdl::Input &input, const gdl::Clock &clock);
  void drawGame(Graphics &ogl, gdl::Clock const &clock);
  FontText *_font;
  gdl::Texture	_text_texture;
  GameGraphics _ogl;
};

#endif
