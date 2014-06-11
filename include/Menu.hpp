#ifndef MENU_HPP_
# define MENU_HPP_

# include <map>
# include <sstream>
# include <Clock.hh>

# include "Game.hpp"
# include "Graphics.hpp"
# include "ACamera.hpp"
# include "PivotingCam.hpp"
# include "Graphics.hpp"

class Menu
{
public:
  Menu(PivotingCam *cam);
  ~Menu();
  bool updateMenu(gdl::Input &input, const gdl::Clock &clock);
  void drawMenu(const gdl::Clock &clock, gdl::AShader* hudshader) const;
  Game *getGame(const glm::ivec2& dim);
  bool finish() const;
private:
  void init();
  Menu(const Menu& m);
  std::string getAscii(gdl::Input &) const;
  bool validNames();
private:
  int _numberPlayer;
  int _numberIa;
  std::vector<std::string> _iaFile;
  Game *_game;
  PivotingCam *_cam;
  FontText *_font;
  glm::vec3 _pos;
  glm::mat4 _ortho;
  enum state {
    Running,
    Option,
    Name,
    Finished
  } _state;
  enum selected {
    Start = 0,
    Options,
    Exit,
    Player,
    Ia,
    IaFile,
    MapFile,
    Return,
    Player1,
    Player2,
    Starting
  } _select;
  enum level {
    Easy = 0,
    Medium,
    Hard
  } _level;
  int _map;
  std::map<level, std::string> _levelFile;
  std::vector<std::string> _mapFile;
  std::string _names[2];
  // std::string _name1;
  // std::string _name2;
  std::map<int, char> _keyToChar;
};

#endif
