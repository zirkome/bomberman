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
#include "IEntity.hpp"
#include "Model.hpp"

class Ia : public IEntity
{
private:
  Map *_currentMap;
  lua_State *_L;
  double _size;
  int _speed;
  int _act;
  int _rotate;
  PMutex _mutex;
  PCondVar _condAct;
  PThread _thread;
  bool _dead;
  bool _running;
  Model *_obj;
  glm::vec2 _vec;
  std::string _fileName;
  std::vector<bool (Ia::*)(double const)> _movePtr;
public:
  int getMap(int x, int y) const;
  double getX() const;
  double getY() const;
  void setX(const double x);
  void setY(const double y);
  void setPos(const glm::vec2 &new_pos);
  void update(gdl::Input &input, gdl::Clock const &clock);
  void draw(gdl::AShader *shader, const gdl::Clock& clock);
  const glm::vec2 &getPos() const;
  void action(int act);
  void *init();
  IEntity::Type getType() const;
  bool nothing(UNUSED double const distance);
  bool moveUp(double const distance);
  bool moveDown(double const distance);
  bool moveLeft(double const distance);
  bool moveRight(double const distance);
  bool bomb(UNUSED double const distance);
public:
  Ia(Map *currentMap, glm::vec2 const &pos, std::string const &fileName);
  ~Ia();
  int exec(); /*!BLOQUANT! call it when the ia can make one action */
};

#endif
