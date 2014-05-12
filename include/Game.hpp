#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <string>

#include <Input.hh>
#include <Clock.hh>

#include "Graphics.hpp"
#include "Map.hpp"
#include "Ia.hpp"
#include "Player.hpp"
#include "Fault.hpp"

#include "Cube.hpp"

class Game
{
public:
  Game(const std::string &saveGame);
  Game(int numberPlayer,
       int numberIA,
       const std::vector<std::string> &algoFileName,
       const std::string &mapName);
  ~Game();

public:
  bool updateGame(gdl::Input &input, const gdl::Clock &clock);
  void drawGame(Graphics &ogl);

private:
  void init();

private:
  std::vector<Ia *> _listIA;
  std::vector<Player *> _players;
  Map *_currentMap;
  Cube	*_cube;
  ACamera* _cam;
};

#endif
