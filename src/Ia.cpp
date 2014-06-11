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
  const glm::vec2& pos = ptr->getPos();
  lua_pop(L, 1);
  lua_pushnumber(L, pos.x);
  lua_pushnumber(L, pos.y);
  return 2; //number of return values
}

int iaGetSizeMap(lua_State *L)
{
  int argc = lua_gettop(L);
  Ia *ptr;

  if (argc != 1)
    throw nFault("iaGetSizeMap need 1 argument (thisptr)");
  ptr = static_cast<Ia *> (lua_touserdata(L, lua_gettop(L)));
  if (ptr == NULL)
    throw nFault("thisptr can't be null");
  const glm::vec2& mapDim = ptr->getMapDimension();
  lua_pop(L, 1);
  lua_pushnumber(L, mapDim.x);
  lua_pushnumber(L, mapDim.y);
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

Ia::Ia(Map *currentMap, glm::vec2 const &pos, std::string const &fileName, const glm::vec4& color)
  : APlayer::APlayer(pos, currentMap, color), _condAct(_mutex), _thread(iaStart, this)
{
  _statusOfObject = OK;
  _running = false;
  _dead = false;
  _fileName = fileName;
  _act = 0;

  _actToSdlKey[1] = SDLK_UP;
  _actToSdlKey[2] = SDLK_DOWN;
  _actToSdlKey[3] = SDLK_LEFT;
  _actToSdlKey[4] = SDLK_RIGHT;
  _actToSdlKey[5] = SDLK_SPACE;

  _actionPtr[SDLK_SPACE] = &Ia::bomb;
  _moveConf[SDLK_UP] = new movementCoef(0, glm::vec2(0.0, 1.0),
				      glm::vec3(0, 0, 1),
				      glm::vec2(0.7, 0.7),
				      glm::vec2(0.2, 0.7));
  _moveConf[SDLK_DOWN] = new movementCoef(180, glm::vec2(0.0, -1.0),
				      glm::vec3(0, 0, -1),
				      glm::vec2(0.7, 0.2),
				      glm::vec2(0.2, 0.2));
  _moveConf[SDLK_LEFT] = new movementCoef(-90, glm::vec2(-1.0, 0.0),
				      glm::vec3(-1, 0, 0),
				      glm::vec2(0.2, 0.7),
				      glm::vec2(0.2, 0.2));

  _moveConf[SDLK_RIGHT] = new movementCoef(90, glm::vec2(1.0, 0.0),
				      glm::vec3(1, 0, 0),
				      glm::vec2(0.7, 0.7),
				      glm::vec2(0.7, 0.2));

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
  lua_pushcfunction(_L, iaGetSizeMap);
  lua_setglobal(_L, "iaGetSizeMap");
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
      luaL_dofile(_L, _fileName.c_str());
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  _running = false;
  return NULL;
}

int Ia::getMap(const int x, const int y) const
{
  IEntity::Type elem;

  if (_map->getPlayersAt(x, y).size() != 0)
    return 7;
  elem = _map->getTypeAt(x, y);
  return (static_cast<int> (elem));
}

int Ia::exec()
{
  if (_running)
    {
      _mutex.lock();
      _condAct.notifyAll();
      _mutex.unlock();
    }
  return _act;
}

void Ia::action(int act)
{
  _act = act;
  _mutex.lock();
  _condAct.wait();
  _mutex.unlock();
  if (_dead)
    {
      _running = false;
      pthread_exit(&act);
    }
}

const glm::vec2& Ia::getPos() const
{
  return _pos;
}

const glm::vec2& Ia::getMapDimension() const
{
  return _map->getDimension();
}

void Ia::update(UNUSED gdl::Input &input, gdl::Clock const &clock)
{
  double distance;
  bool hasMoved;

  exec();
  distance = clock.getElapsed() * _speed;
  if (distance > 1.0)
    distance = 1.0;

  std::map<int, int>::iterator key = _actToSdlKey.find(_act);

  // si _act correspond a une key
  if (key != _actToSdlKey.end())
    {
      int	sdlKey = key->second;
      // sdlKey = *key;

      std::map<int, movementCoef *>::iterator sdlKeyMove = _moveConf.find(sdlKey);

      // si le key est pour move
      if (sdlKeyMove != _moveConf.end())
        {
          hasMoved = movePlayer(_moveConf[key->second], distance);
          updateAnim(hasMoved);
          return;
        }
      else
        {
          // sinon on check dans le tableau de ptointeur sur fonction
          for (actionPtr::iterator it = _actionPtr.begin(); it != _actionPtr.end(); ++it)
            {
              if (it->first == sdlKey)
                {
                  (this->*_actionPtr[sdlKey])();
                  return;
                }
            }
        }
    }
}

bool Ia::nothing(UNUSED double const distance)
{
  if (_status != STOP_WALK)
    (*_obj)->setCurrentSubAnim("stop_walk");
  _status = STOP_WALK;
  return true;
}
