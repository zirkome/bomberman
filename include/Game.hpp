#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <string>

#include <Input.hh>

#include "Graphics.hpp"
#include "Map.hpp"
#include "Ia.hpp"
#include "Player.hpp"
#include "Fault.hpp"

class Game
{
private:
  std::vector<Ia *> _listIA;
  std::vector<Player *> _players;
  Map *_currentMap;

public:
  Game(const std::string &saveGame);
  Game(int numberPlayer,
       int numberIA,
       const std::vector<std::string> &algoFileName,
       const std::string &mapName);
  ~Game();

public:
  bool updateGame(gdl::Input &input);
  void drawGame(Graphics &ogl);
};

#endif
