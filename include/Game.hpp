#ifndef GAME_HPP_
# define GAME_HPP_

# include <vector>
# include <string>
# include <list>

# include <boost/archive/binary_oarchive.hpp>
# include <boost/archive/binary_iarchive.hpp>
# include <boost/serialization/list.hpp>
# include <boost/serialization/vector.hpp>
# include <Input.hh>
# include <Clock.hh>
# include <Texture.hh>

# include "config.h"
# include "Graphics.hpp"
# include "ArmagetroCam.hpp"
# include "BasicCam.hpp"
# include "Map.hpp"
# include "Ia.hpp"
# include "PlayerManager.hpp"
# include "Fault.hpp"
# include "FontText.hpp"
# include "Cube.hpp"
# include "Pan.hpp"
# include "Placement.hpp"
# include "SkyBox.hpp"
# include "Pause.hpp"

class Game
{
  friend class boost::serialization::access;

public:
  Game(const glm::ivec2& win, const std::string &saveGame);
  Game(const glm::ivec2& win,
       int numberPlayer,
       int numberIA,
       const std::string &algoFileName,
       const std::string names[2],
       const std::string &mapName = "");
  ~Game();

public:
  bool updateGame(gdl::Input &input, const gdl::Clock &clock);
  void drawGame(gdl::Clock const &clock);

private:
  void init(const glm::ivec2& win);

  void drawHud(gdl::AShader *shader, gdl::Clock const &clock) const;

public:
  template<class Archive>
  void serialize(Archive & ar, UNUSED const unsigned int version)
  {
    for (std::vector<Ia*>::iterator it = _listIA.begin(), end = _listIA.end();
    	 it != end; it++)
      ar & *(*it);
    // for (std::vector<PlayerManager*>::iterator it = _players.begin(), end = _players.end();
    // 	 it != end; it++)
    //   ar & *(*it);
    ar & *_currentMap;
  }

private:
  std::vector<Ia *> _listIA;
  std::vector<PlayerManager*> _players;
  Pause _pause;
  Map *_currentMap;
  GameGraphics _ogl;
  SharedPointer<Texture> _groundTex;
  bool _isPaused;
};

#endif
