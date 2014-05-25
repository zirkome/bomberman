#include "EntitiesFactory.hpp"
#include "Game.hpp"
#include "AShader.hh"
#include "ArmagetroCam.hpp"
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
  Placement place(_currentMap);
  i = 0;
  size = algoFileName.size();
  while (i < numberIA)
    {
      if (size != 0)
        _listIA.push_back(new Ia(_currentMap, place.getNewPos(), algoFileName[i % size]));
      else
        _listIA.push_back(new Ia(_currentMap, place.getNewPos(), "Path/to/default/ia.lua"));
      i++;
    }

  i = 0;
  while (i < numberPlayer)
    {
      _players.push_back(new Player(place.getNewPos(), _currentMap));
      i++;
    }
  for (std::vector<Ia *>::iterator it = _listIA.begin() ; it != _listIA.end(); ++it)
    if (_currentMap->addEntity(*it) != true)
      throw nFault("Error in the initializiation of the map");
  for (std::vector<Player *>::iterator it = _players.begin() ; it != _players.end(); ++it)
    if (_currentMap->addEntity(*it) != true)
      throw nFault("Error in the initializiation of the map");


  init(win);
}

void Game::init(glm::ivec2 win)
{
  /* TODO : init game and load 3d models */
  glm::vec2 playerPos = _players.front()->getPos();
  _ground = new Pan(_currentMap->getDimension());
  _cam = new FreeCam;

  _ground->initialize();
  _ground->scale(glm::vec3(0.5f, 0.5f, 1.0f));
  _ground->translate(glm::vec3(-0.5f, 0, -0.5f));
  _ground->scale(glm::vec3(_currentMap->getDimension().x, _currentMap->getDimension().y, 1.0f));

  _ground->translate(glm::vec3((float)_currentMap->getDimension().x / 2.0,
			       -0.5f,
			       (float)_currentMap->getDimension().y / 2));
  _ground->rotate(glm::vec3(1, 0, 0), 90.0);

  _font = new FontText(RES_TEXTURE "font.tga");
  _ogl.init(win);
}

Game::~Game()
{
  delete _cam;
}

bool Game::updateGame(gdl::Input &input, const gdl::Clock &clock)
{
  glm::vec2 playerPos = _players.front()->getPos();
  // _cam->update(glm::vec3(playerPos.x, playerPos.y, 0));
  _cam->update(input, clock);

  /* TODO : move players, explose bomb, ... */
  std::list<IEntity *>	&list = _currentMap->getMap();

  for (std::list<IEntity *>::iterator it = list.begin() ; it != list.end() ; it++)
    {
      (*it)->update(input, clock);
    }
  return true;
}

void Game::drawGame(UNUSED gdl::Input &input, gdl::Clock const &clock) const
{
  gdl::AShader *shader = _ogl.getShader();

  _ogl.startFrame();
  shader->setUniform("view", _cam->project());

  AssetsManager::getInstance()->getAssets<gdl::Texture>(IEntity::GROUND)->bind();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

  _ground->draw(shader, clock);

  for (Map::iterator it = _currentMap->begin(), end = _currentMap->end(); it != end; ++it) {
    (*it)->draw(shader, clock);
  }

  _font->displayText("ABCDEFGHIJKLMNOPQRSTUVWXYZ", glm::vec3(0,1,0), 1, shader);
  _ogl.processFrame(_cam->getPosition());
  // Menu and Game have they own Graphics class
}
