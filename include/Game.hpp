#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <string>
#include "Map.hpp"
#include "Ia.hpp"
#include "Player.hpp"
#include "Graphics.hpp"
#include "Fault.hpp"

class Game
{
private:
  std::vector<Ia *> _listIA;
  std::vector<Player *> _players;
  Map *_currentMap;
public:
  Game(std::string const &saveGame);
  Game(int numberPlayer, int numberIA, std::vector<std::string> const &algoFileName, std::string const &mapName);
  ~Game();
  bool updateGame(Graphics &interface);
  void drawGame(Graphics &interface);
};

#endif
