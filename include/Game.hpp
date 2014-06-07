#ifndef GAME_HPP_
# define GAME_HPP_

# include <vector>
# include <string>
# include <list>

# include <Input.hh>
# include <Clock.hh>
# include <Texture.hh>
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

#include "BonusWalk.hpp"

class Game
{
public:
  Game(const glm::ivec2& win, const std::string &saveGame);
  Game(const glm::ivec2& win,
       int numberPlayer,
       int numberIA,
       const std::string &algoFileName,
       const std::string &mapName = "");
  ~Game();

public:
  bool updateGame(gdl::Input &input, const gdl::Clock &clock);
  void drawGame(gdl::Clock const &clock);

private:
  void init(const glm::ivec2& win);

  void drawHud(gdl::AShader *shader, gdl::Clock const &clock) const;

private:
  std::vector<Ia *> _listIA; //Why not Ia and player doesn't hineretaded from the same class ?
  std::vector<PlayerManager*> _players;

  Map *_currentMap;
  GameGraphics _ogl;
};

#endif
