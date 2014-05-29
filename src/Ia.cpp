#include "Ia.hpp"

int iaGetPos(lua_State *L)
{
  int argc = lua_gettop(L);
  Ia *ptr;

  if (argc != 1)
    throw nFault("iaGetPos need 1 argument (thisptr)");
  ptr = static_cast<Ia *> (lua_touserdata(L, lua_gettop(L)));
  if (ptr == NULL)
    throw nFault("thisptr can't be null");
  lua_pop(L, 1);
  lua_pushnumber(L, ptr->getX());
  lua_pushnumber(L, ptr->getY());
  return 2; //number of return values
}

int iaGetMap(lua_State *L)
{
  int argc = lua_gettop(L);
  Ia *ptr;
  int x, y;

  if (argc != 3)
    throw nFault("iaGetMap need 3 arguments (x, y, thisptr)");
  ptr = static_cast<Ia *> (lua_touserdata(L, lua_gettop(L)));
  if (ptr == NULL)
    throw nFault("thisptr can't be null");
  lua_pop(L, 1);
  y = lua_tonumber(L, lua_gettop(L)); //the order of args is inverse
  lua_pop(L, 1);
  x = lua_tonumber(L, lua_gettop(L));
  lua_pop(L, 1);
  lua_pushnumber(L, ptr->getMap(x, y));
  return 1;
}

int iaAction(lua_State *L)
{
  int argc = lua_gettop(L);
  Ia *ptr;
  int act;

  if (argc != 2)
    throw nFault("iaAction need 2 arguments (act, thisptr)");
  ptr = static_cast<Ia *> (lua_touserdata(L, lua_gettop(L)));
  if (ptr == NULL)
    throw nFault("thisptr can't be null");
  lua_pop(L, 1);
  act = lua_tonumber(L, lua_gettop(L));
  lua_pop(L, 1);
  ptr->action(act);
  return 0;
}

int iaLaunch(lua_State *L)
{
  int argc = lua_gettop(L);
  Ia *ptr;

  if (argc != 1)
    throw nFault("iaLaunch need 1 arguments (thisptr)");
  ptr = static_cast<Ia *> (lua_touserdata(L, lua_gettop(L)));
  if (ptr == NULL)
    throw nFault("thisptr can't be null");
  lua_pop(L, 1);
  ptr->action(-1);
  return 0;
}

void *iaStart(void *ptr)
{
  return (static_cast<Ia *> (ptr))->init();
}

Ia::Ia(Map *currentMap, glm::vec2 const &pos, std::string const &fileName)
: _condAct(_mutex), _thread(iaStart, this)
{
  _speed = 3;
  _running = false;
  _vec = pos;
  _dead = false;
  _fileName = fileName;
  _act = 0;
  _status = STANDBY;
  _size = 0.7;

  _obj = new Model(RES_MODEL "marvin.fbx");
  _obj->translate(glm::vec3(pos.x, -0.5, pos.y));
  _obj->scale(glm::vec3(0.0025, 0.0025, 0.0025));

  _obj->createSubAnim(0, "standby", 0, 0);
  _obj->createSubAnim(0, "walk", 42, 63);
  _obj->createSubAnim(0, "stop_walking", 64, 121);

  _movePtr.push_back(&Ia::nothing);
  _movePtr.push_back(&Ia::moveUp);
  _movePtr.push_back(&Ia::moveDown);
  _movePtr.push_back(&Ia::moveLeft);
  _movePtr.push_back(&Ia::moveRight);
  _movePtr.push_back(&Ia::bomb);

  _L = luaL_newstate();
  if (_L == NULL)
    throw nFault("Init lua fail");

  _map = currentMap;

  luaL_openlibs(_L);

  lua_pushcfunction(_L, iaGetPos);
  lua_setglobal(_L, "iaGetPos");
  lua_pushcfunction(_L, iaGetMap);
  lua_setglobal(_L, "iaGetMap");
  lua_pushcfunction(_L, iaLaunch);
  lua_setglobal(_L, "iaLaunch");
  lua_pushcfunction(_L, iaAction);
  lua_setglobal(_L, "iaAction");
  lua_pushlightuserdata(_L, this);
  lua_setglobal(_L, "thisptr");

  _thread.start();
}

Ia::~Ia()
{
  _dead = true;
  _condAct.notifyAll();
  lua_close(_L);
}

void *Ia::init()
{
  try
    {
      _running = true;
      luaL_dofile(_L,"script/test.lua");
      //  luaL_dofile(_L,_fileName.c_str());
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  _running = false;
  _mutex.lock();
  _condAct.notifyAll();
  _mutex.unlock();
  return NULL;
}

int Ia::getMap(const int x, const int y) const
{
  IEntity::Type elem;

  elem = _map->getTypeAt(x, y);
  return (static_cast<int> (elem));
}

int Ia::exec()
{
  if (_running)
    {
      _mutex.lock();
      _condAct.notifyAll();
      _condAct.wait();/* TODO : change that */
      _mutex.unlock();
    }
  return _act;
}

void Ia::action(int act)
{
  _act = act;
  _mutex.lock();
  if (_act != -1)
    _condAct.notifyAll();
  _condAct.wait();
  _mutex.unlock();
  if (_dead)
    {
      _running = false;
      _mutex.lock();
      _condAct.notifyAll();
      _mutex.unlock();
      pthread_exit(&act);
    }
}

double Ia::getX() const
{
  return _vec.x;
}

double Ia::getY() const
{
  return _vec.y;
}

void Ia::setX(const double x)
{
  _vec.x = x;
}

void Ia::setY(const double y)
{
  _vec.y = y;
}

void Ia::update(UNUSED gdl::Input &input, gdl::Clock const &clock)
{
  double distance;

  exec();
  distance = clock.getElapsed() * _speed;
  if (_act >= 0 && _act < 6)
    (this->*_movePtr[_act])(distance);
  else
    (this->*_movePtr[0])(distance);
}

bool Ia::nothing(UNUSED double const distance)
{
  if (_status != STOP_WALK)
    _obj->setCurrentSubAnim("stop_walk");
  _status = STOP_WALK;
  return true;
}
