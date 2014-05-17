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
#include "PMutex.hpp"
#include "PCondVar.hpp"
#include "PThread.hpp"

class Ia
{
private:
  Map *_currentMap;
  lua_State *_L;
  int _x;
  int _y;
  int _act;
  PMutex _mutex;
  PCondVar _condAct;
  PThread _thread;
  bool _dead;
  std::string _fileName;
public:
  int getMap(int x, int y) const;
  int getX() const;
  int getY() const;
  void setDead();
  void action(int act) const;
  void *init();
  Ia(Map *currentMap, int x, int y, std::string const &fileName);
  ~Ia();
  int exec(); /*!BLOQUANT! call it when the ia can make one action */
};

#endif
