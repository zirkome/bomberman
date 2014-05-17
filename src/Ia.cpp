#include "Ia.hpp"

int iaGetPos(lua_State *L)
{
  int argc = lua_gettop(L);
  const Ia *ptr;

  if (argc != 1)
    throw nFault("iaGetPos need 1 argument (thisptr)");
  ptr = static_cast<const Ia *> (lua_topointer(L, lua_gettop(L)));
  lua_pushnumber(L, ptr->getX());
  lua_pushnumber(L, ptr->getY());
  return 2; //number of return values
}

int iaGetMap(lua_State *L)
{
  int argc = lua_gettop(L);
  const Ia *ptr;
  int x, y;

  if (argc != 3)
    throw nFault("iaGetMap need 3 arguments (x, y, thisptr)");
  ptr = static_cast<const Ia *> (lua_topointer(L, lua_gettop(L)));
  y = lua_tonumber(L, lua_gettop(L)); //the order of args is inverse
  x = lua_tonumber(L, lua_gettop(L));
  lua_pushnumber(L, ptr->getMap(x, y));
  return 1;
}

int iaAction(lua_State *L)
{
  int argc = lua_gettop(L);
  const Ia *ptr;
  int act;

  if (argc != 2)
    throw nFault("iaAction need 2 arguments (act, thisptr)");
  ptr = static_cast<const Ia *> (lua_topointer(L, lua_gettop(L)));
  act = lua_tonumber(L, lua_gettop(L));
  ptr->action(act);
  return 0;
}

Ia::Ia(Map *currentMap, int x, int y)
{
  _currentMap = currentMap;
  _x = x;
  _y = y;
}

Ia::Ia(std::string const &fileName, Map *currentMap, int x, int y)
{
  _x = x;
  _y = y;
  _L = luaL_newstate();
  if (_L == NULL)
    throw nFault("Init lua fail");

  _currentMap = currentMap;

  // create thread and condvar here

  luaL_openlibs(_L);

  lua_pushcfunction(_L, iaGetPos);
  lua_setglobal(_L, "iaGetPos");
  lua_pushcfunction(_L, iaGetMap);
  lua_setglobal(_L, "iaGetMap");
  lua_pushlightuserdata(_L, this);
  lua_setglobal(_L, "thisptr");

  luaL_dofile(_L,"script/test.lua");
  (void) fileName;
}

Ia::~Ia()
{
  lua_close(_L);
}

int Ia::getMap(const int x, const int y) const
{
  IEntity::Type elem;

  elem = _currentMap->getTypeAt(x, y);
  return (static_cast<int> (elem));
}

void Ia::action(int act) const
{
  /* how to do this with a const ????*/
  (void) act;
  /* condvar to synchonise with the gui*/
}

int Ia::getX() const
{
  return _x;
}

int Ia::getY() const
{
  return _y;
}
