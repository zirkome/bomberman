#include "Game.hpp"
#include "AShader.hh"
#include <Geometry.hh>

Game::Game(std::string const &saveGame)
{
  if (saveGame == "")
    throw nFault("The file name of the game is too short");
  /* TODO : load the saved game in saveGame file and load 3d models */
}

Game::Game(int numberPlayer, int numberIA, std::vector<std::string> const &algoFileName,
	   std::string const &mapName = "")
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
  _cube = new Cube;
  _cube->initialize();
}

Game::~Game()
{
  delete _cube;
}

bool Game::updateGame(gdl::Input &input, gdl::Clock &clock)
{
  // (void) input;
  // (void) clock;
  /* TODO : move players, explose bomb, ... */
  _cube->update(clock, input);
  return true;
}

void Game::drawGame(Graphics &ogl)
{
  // (void) ogl;
  gdl::AShader *shader = ogl.getShader();

  shader->bind();

  shader->setUniform("view", glm::lookAt(glm::vec3(0, 0, -2.0f),
					 glm::vec3(0, 0, 0),
					 glm::vec3(0, 1, 0)));
  shader->setUniform("projection", glm::perspective(60.0f, 1024.0f / 900.0f, 0.01f, 500.0f));
  _cube->draw(ogl.getShader());
}
