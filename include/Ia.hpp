#ifndef IA_HPP_
#define IA_HPP_

#include <string>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "Map.hpp"
#include "Fault.hpp"

class Ia
{
private:
  Map *_currentMap;
  lua_State *_L;
  int getMap(int x, int y);
  void action(int act);
public:
  Ia(std::string const &fileName, Map *currentMap);
  Ia(Map *currentMap);// ia basic if we have no files
  ~Ia();
  void exec(); /*!BLOQUANT! call it when the ia can make one action */
};

#endif
