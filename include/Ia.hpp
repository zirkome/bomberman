#ifndef IA_HPP_
#define IA_HPP_

#include <string>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "Map.hpp"
#include "Fault.hpp"

class Ia
{
private:
  Map *_currentMap;
  lua_State *_L;
  int _x;
  int _y;
public:
  int getMap(int x, int y) const;
  int getX() const;
  int getY() const;
  void action(int act) const;
  Ia(std::string const &fileName, Map *currentMap, int x, int y);
  Ia(Map *currentMap, int x, int y);// ia basic if we have no files
  ~Ia();
  void exec(); /*!BLOQUANT! call it when the ia can make one action */
};

#endif
