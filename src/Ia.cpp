#include "Ia.hpp"

Ia::Ia(Map *currentMap)
{
  _currentMap = currentMap;
}

Ia::Ia(std::string const &fileName, Map *currentMap)
{
  std::cout << "1" << std::endl;
  _L = lua_open();
  std::cout << "2" << std::endl;
  if (_L == NULL)
    throw nFault("Init lua fail");
  _currentMap = currentMap;
  //  luaopen_io(_L); /* provides io.* for debug ia */
  lua_pushcfunction(_L, luaopen_io);
  std::cout << "3" << std::endl;
  luaopen_base(_L);
  std::cout << "4" << std::endl;
  luaopen_table(_L);
  std::cout << "5" << std::endl;
  luaopen_string(_L);
  std::cout << "6" << std::endl;
  luaopen_math(_L);
  std::cout << "7" << std::endl;
  luaL_openlibs(_L);
  std::cout << "8" << std::endl;
  //  lua_register(_L, "getMap", getMap);/*Get a case of map*/
  // lua_register(_L, "action", action);/* when ia have choose what to do */
  if (luaL_loadfile(_L, "srcipt/test.lua") == 0)
    {
      std::cout << "9" << std::endl;
      lua_pcall(_L, 0, LUA_MULTRET, 0);/* execute Lua program */
    }
  std::cout << "10" << std::endl;
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
