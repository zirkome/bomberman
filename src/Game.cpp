#include "Game.hpp"

Game::Game(std::string const &saveGame)
{
  if (saveGame == "")
    throw nFault("The file name of the game is too short");
  /* TODO : load the saved game in saveGame file and load 3d models */
}

Game::Game(int numberPlayer, int numberIA, std::vector<std::string> const &algoFileName, std::string const &mapName = "")
{
  int i, size;

  if (numberIA < 0 || numberPlayer < 0 || (numberPlayer + numberIA <= 1))
    throw nFault("You need two players");

  _currentMap = new Map(mapName);

  i = 0;
  size = algoFileName.size();
  while (i < numberIA)
    {
      if (size != 0)
        _listIA.push_back(new Ia(algoFileName[i % size], _currentMap));
      else
        _listIA.push_back(new Ia(_currentMap));
      i++;
    }

  i = 0;
  while (i < numberPlayer)
    {
      _players.push_back(new Player(_currentMap));
      i++;
    }
  /* TODO : init game and load 3d models */
}

Game::~Game()
{
}

bool Game::updateGame(gdl::Input &input, gdl::Clock &clock)
{
  (void) input;
  (void) clock;
  /* TODO : move players, explose bomb, ... */
  return true;
}

void Game::drawGame(Graphics &ogl)
{
  (void) ogl;
  /* TODO : draw the curent game */
}
