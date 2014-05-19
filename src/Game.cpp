#include "EntitiesFactory.hpp"
#include "Game.hpp"
#include "AShader.hh"
#include "FreeCam.hpp"
#include "FpsCam.hpp"
#include "TrackCam.hpp"
#include "OrthoCam.hpp"
#include "config.h"
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

  if (numberIA < 0 || numberPlayer < 0 // || (numberPlayer + numberIA <= 1)
      )
    throw nFault("You need two players");

  _currentMap = new Map(mapName);

  i = 0;
  size = algoFileName.size();
  while (i < numberIA)
    {
      if (size != 0)
        _listIA.push_back(new Ia(_currentMap, 0, 0, algoFileName[i % size]));
      else
        _listIA.push_back(new Ia(_currentMap, 0, 0, "Path/to/default/ia.lua"));
      i++;
    }

  i = 0;
  while (i < numberPlayer)
    {
      _players.push_back(new Player(glm::vec2(1,1)));
      i++;
    }
  init(win);
}

void Game::init(glm::ivec2 win)
{
  /* TODO : init game and load 3d models */
  _cam = new TrackCam(glm::vec3(_currentMap->getWidth() / 2, 0.0, _currentMap->getLength() / 2));
  // std::list<IEntity *>	&list = _currentMap->getMap();

  // for (std::list<IEntity *>::iterator it = list.begin(); it != list.end(); it++)
  //   {
  //     if (*it != NULL)
  //       (*it)->getObj()->initialize();
  //   }
  _font = new FontText(RES_ASSETS "font.tga");
  _ogl.init(win);
}

Game::~Game()
{
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

void Game::drawGame(gdl::Clock const &clock) const
{
  gdl::AShader *shader = _ogl.getShader();
  const std::list<IEntity *> &list = _currentMap->getMap();

  _ogl.startFrame();
  shader->setUniform("view", _cam->project());

  for (std::list<IEntity*>::const_iterator it = list.begin(), end = list.end();
       it != end; ++it)
    {
      if (*it != NULL)
        (*it)->draw(shader, clock);
    }

  for (std::vector<Player *>::const_iterator it = _players.begin(); it != _players.end(); ++it)
    {
      (*it)->draw(shader, clock);
    }

  _font->displayText("Hello", glm::vec2(0,0), 10, shader);
  _ogl.processFrame(_cam->getPosition());
  // Menu and Game have they own Graphics class
}
