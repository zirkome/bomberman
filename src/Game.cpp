#include <sstream>
#include <iomanip>
#include <Geometry.hh>

#include "ResourceManager.hpp"
#include "EntitiesFactory.hpp"
#include "Game.hpp"
#include "AShader.hh"
#include "ArmagetroCam.hpp"
#include "FreeCam.hpp"
#include "FpsCam.hpp"
#include "TrackCam.hpp"
#include "OrthoCam.hpp"
#include "config.h"
#include "BasicCam.hpp"

Game::Game(const glm::ivec2& win, std::string const &saveGame)
{
  if (saveGame == "")
    throw nFault("The file name of the game is too short");
  /* TODO : load the saved game in saveGame*/
  init(win);
}

Game::Game(const glm::ivec2& win, int numberPlayer, int numberIA, std::string const & algoFileName,
           std::string const &mapName)
{
  int i;

  if (numberIA < 0 || numberPlayer < 0)
    throw nFault("You need two players");

  if (mapName == "")
    _currentMap = new Map(100, 100);
  else
    _currentMap = new Map(mapName);

  Placement place(_currentMap);

  i = 0;
  while (i < numberIA)
    {
      _listIA.push_back(new Ia(_currentMap, place.getNewPos(), algoFileName, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
      i++;
    }

  i = 0;
  while (i < numberPlayer)
    {
      _players.push_back(new PlayerManager(place.getNewPos(), _currentMap, (i == 0 ? true : false)));
      i++;
    }
  for (std::vector<Ia *>::iterator it = _listIA.begin() ; it != _listIA.end(); ++it)
    if (_currentMap->addEntity(*it) != true)
      throw nFault("Error in the initializiation of the map");
  for (std::vector<PlayerManager*>::iterator it = _players.begin() ; it != _players.end(); ++it)
    if (_currentMap->addEntity(&(*it)->getPlayer()) != true)
      throw nFault("Error in the initializiation of the map");


  init(win);
}

void Game::init(const glm::ivec2& win)
{
  glm::vec2 mapDim = _currentMap->getDimension();
  _ogl.init(win, glm::ivec2(mapDim.x, mapDim.y), (_players.size() == 2));
}

Game::~Game()
{
  for (std::vector<Ia*>::iterator it = _listIA.begin();
       it != _listIA.end(); ++it)
    delete *it;
  for (std::vector<PlayerManager*>::iterator it = _players.begin();
       it != _players.end(); ++it)
    delete *it;
  delete _currentMap;
}

bool Game::updateGame(gdl::Input &input, const gdl::Clock &clock)
{
  std::list<Map::iterator> listMapToDelete;
  for (Map::iterator it = _currentMap->begin(); it != _currentMap->end(); ++it) {
      (*it)->update(input, clock);
      if ((*it)->getStatus() == IEntity::DESTROY || (*it)->getStatus() == IEntity::REMOVE)
        listMapToDelete.push_back(it);
    }

  Map::LMap playerList = _currentMap->getPlayerList();
  for (Map::iterator it = playerList.begin(), end = playerList.end(); it != end; ++it) {
      if ((*it)->getStatus() == IEntity::DESTROY) {
          //TODO HANDLE DEFEAT
        }
      else
	{
	  (*it)->update(input, clock);
	}
  }

  //Delete every elements which are DESTROYs
  while (!listMapToDelete.empty()) {
    //create bonus id box is destroyed
    std::list<IEntity *>::iterator it = listMapToDelete.front();

    if ((*it)->getType() == IEntity::BOX)
      std::cout << "bonus" << std::endl;
    if ((*it)->getStatus() == IEntity::DESTROY)
      delete *it;
    _currentMap->getMap().erase(it);
    listMapToDelete.pop_front();
  }

  for (std::vector<PlayerManager*>::iterator it = _players.begin();
       it != _players.end(); ++it)
    (*it)->update(*_currentMap);

  _ogl.updateGraphic(clock);
  return true;
}

void Game::drawGame(gdl::Clock const &clock)
{
  _ogl.drawGame(clock, _players);
  drawHud(_ogl.getShader(), clock);
}

void Game::drawHud(gdl::AShader* shader, gdl::Clock const &clock) const
{
  _ogl.setHudProj();

  const FontText& font = _ogl.getTextWriter();
  glm::mat4 textMat;

  std::stringstream ss;
  static double elapsed = 0.0;
  static unsigned int k = 0;
  ++k;
  if (k % 20 == 0)
    elapsed = clock.getElapsed();
  ss << std::setprecision(2) << 1.0 / elapsed << " FPS";

  textMat = glm::translate(glm::mat4(1), glm::vec3(0.8, 0.97, 0.0));
  textMat = glm::scale(textMat, glm::vec3(0.5, 0.5, 0.0));
  font.displayText(ss.str(), (elapsed <= 0.017) ? glm::vec4(0.0f, 1.0f, 0.0f, 0.8f) : glm::vec4(1.0f, 0.0f, 0.0f, 0.8f), textMat, shader);
}
