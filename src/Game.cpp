#include "Game.hpp"
#include "AShader.hh"
#include "FreeCam.hpp"
#include <Geometry.hh>

Game::Game(std::string const &saveGame)
{
  if (saveGame == "")
    throw nFault("The file name of the game is too short");
  /* TODO : load the saved game in saveGame*/

  init();
}

Game::Game(int numberPlayer, int numberIA, std::vector<std::string> const & algoFileName, std::string const &mapName = "")
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
  init();
}

AObject* _cube2;
AObject* _cube3;
AObject* _cube4;
AObject* _cube5;
AObject* _cube6;

void Game::init()
{
  /* TODO : init game and load 3d models */
  _cube = new Cube;
  _cube->initialize();

  _cube2 = new Cube;
  _cube2->initialize();

  _cube3 = new Cube;
  _cube3->initialize();

  _cube4 = new Cube;
  _cube4->initialize();

  _cube5 = new Cube;
  _cube5->initialize();

  _cube6 = new Cube;
  _cube6->initialize();

  _cube2->translate(glm::vec3(0, 0, -15));
  _cube3->translate(glm::vec3(-5, 0, -10));
  _cube4->translate(glm::vec3(5, 0, -10));
  _cube5->translate(glm::vec3(0, 5, -10));
  _cube6->translate(glm::vec3(0, -5, -10));
  _cam = new FreeCam();
}

Game::~Game()
{
  delete _cube;
  delete _cam;
}

bool Game::updateGame(gdl::Input &input, const gdl::Clock &clock)
{
  _cam->update(input, clock);

  /* TODO : move players, explose bomb, ... */
  _cube->update(clock, input);
  return true;
}

void Game::drawGame(Graphics & ogl)
{
  gdl::AShader *shader = ogl.getShader();

  ogl.startFrame();
  shader->setUniform("view", _cam->project());
  _cube->draw(ogl.getShader());
  _cube2->draw(ogl.getShader());
  _cube3->draw(ogl.getShader());
  _cube4->draw(ogl.getShader());
  _cube5->draw(ogl.getShader());
  _cube6->draw(ogl.getShader());
}
