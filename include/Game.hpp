#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>
#include <vector>

#include <Graphics.hpp>
#include <Ia.hpp>
#include <Player.hpp>
#include <SkyBox.hpp>
#include <Texture.hpp>
#include "Pan.hpp"
#include "Placement.hpp"
#include "FontText.hpp"

class ACamera;
class FontText;

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
  void drawGame(gdl::Input &input, gdl::Clock const &clock);

private:
  void init(const glm::ivec2& win);

  void drawGraphicObject(gdl::AShader *shader, gdl::Clock const &clock) const;

private:
  std::vector<Ia *> _listIA; //Why not Ia and player doesn't hineretaded from the same class ?
  std::vector<Player *> _players; //Those are IEntity
  Map *_currentMap;
  glm::ivec2 _win;
  Cube *_cube;
  ACamera* _cam;
  FontText *_font;
  SharedPointer<Texture> _groundTex;
  GameGraphics _ogl;
  glm::mat4 _ortho;
  Pan *_ground;
  SkyBox _skybox;
};

#endif
