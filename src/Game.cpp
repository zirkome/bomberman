#include "EntitiesFactory.hpp"
#include "Game.hpp"
#include "AShader.hh"
#include "FreeCam.hpp"
#include <Geometry.hh>

Game::Game(const glm::ivec2& win, std::string const &saveGame)
{
  if (saveGame == "")
    throw nFault("The file name of the game is too short");
  /* TODO : load the saved game in saveGame*/

  init(win);
}

Game::Game(const glm::ivec2& win, int numberPlayer, int numberIA, std::vector<std::string> const & algoFileName,
           std::string const &mapName)
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
  init(win);
}

void Game::init(glm::ivec2 win)
{
  /* TODO : init game and load 3d models */
  _cam = new FreeCam();
  std::list<IEntity *>	&list = _currentMap->getMap();

  for (std::list<IEntity *>::iterator it = list.begin() ; it != list.end() ; it++)
    {
      if (*it != NULL)
        (*it)->getObj()->initialize();
    }
  // _font = new FontText(_text_texture, 19, 29);
  _ogl.init(win);
}

Game::~Game()
{
  // delete _cube;
  delete _cam;
}

bool Game::updateGame(gdl::Input &input, const gdl::Clock &clock)
{
  _cam->update(input, clock);

  /* TODO : move players, explose bomb, ... */
  std::list<IEntity *>	&list = _currentMap->getMap();

  for (std::list<IEntity *>::iterator it = list.begin() ; it != list.end() ; it++)
    {
      if (*it != NULL)
        (*it)->update(input, clock);
    }
  return true;
}

void Game::drawGame(gdl::Clock const &clock)
{
  (void)clock;
  gdl::AShader *shader = _ogl.getShader();
  std::list<IEntity *>	&list = _currentMap->getMap();

  _ogl.startFrame();
  shader->setUniform("view", _cam->project());
  for (std::list<IEntity *>::iterator it = list.begin() ; it != list.end() ; it++)
    {
      if (*it != NULL)
        (*it)->getObj()->draw(shader);
    }
  // Menu and Game have they own Graphics class
}
