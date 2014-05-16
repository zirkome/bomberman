#include "Ia.hpp"

Ia::Ia(Map *currentMap)
{
  _currentMap = currentMap;
}

Ia::Ia(std::string const &fileName, Map *currentMap)
{
  _L = luaL_newstate();
  if (_L == NULL)
    throw nFault("Init lua fail");
  _currentMap = currentMap;

  luaL_openlibs(_L);
  luaL_dofile(_L,"script/test.lua");

  (void) fileName;
}

Ia::~Ia()
{
  lua_close(_L);
}

int Ia::getMap(int x, int y)
{
  (void) x;
  (void) y;
  //  _currentMap[x][y]
  return 0;
}

void Ia::action(int act)
{
  (void) act;
  /* condvar to synchonise with the gui*/
}
