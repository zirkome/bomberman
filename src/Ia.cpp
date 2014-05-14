#include "Ia.hpp"

Ia::Ia(Map *currentMap)
{
  _currentMap = currentMap;
}

Ia::Ia(std::string const &fileName, Map *currentMap)
{
  _L = lua_open();
  if (_L == NULL)
    throw nFault("Init lua fail");
  _currentMap = currentMap;
  luaopen_io(_L); /* provides io.* for debug ia */
  luaopen_base(_L);
  luaopen_table(_L);
  luaopen_string(_L);
  luaopen_math(_L);
  luaL_openlibs(_L);

  //  lua_register(_L, "getMap", getMap);/*Get a case of map*/
  // lua_register(_L, "action", action);/* when ia have choose what to do */
  if (luaL_loadfile(_L, "srcipt/test.lua") == 0)
    lua_pcall(_L, 0, LUA_MULTRET, 0);/* execute Lua program */
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
