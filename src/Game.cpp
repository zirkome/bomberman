#include "Game.hpp"


Game::Game(std::string const &saveGame)
{
  if (saveGame == "")
    throw nFault("The name of the saved game is too short");
  /* TODO : load the saved game in saveGame file and load 3d models */
}

Game::Game(int NumberPlayer, int NumberIA, std::vector<std::string> const &algoFileName, std::string const &mapName = "")
{
  int i, size;

  if (NumberIA < 0 || NumberPlayer < 0 || (NumberPlayer + NumberIA <= 1))
    throw nFault("You need two players");

  _currentMap = new Map(mapName);

  i = 0;
  size = algoFileName.size();
  while (i < NumberIA)
    {
      if (size != 0)
	_listIA.push_back(new Ia(algoFileName[i % size], _currentMap));
      else
	_listIA.push_back(new Ia(_currentMap));
      i++;
    }

  i = 0;
  while (i < NumberPlayer)
    _players.push_back(new Player(_currentMap));
  /* TODO : init game and load 3d models */
}

Game::~Game()
{
}

bool Game::updateGame(Graphics &interface)
{
  (void) interface;
  /* TODO : move players, explose bomb, ... */
  return true;
}

void Game::drawGame(Graphics &interface)
{
  (void) interface;
  /* TODO : draw the curent game */
}
