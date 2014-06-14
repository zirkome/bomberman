#ifndef IA_HPP_
# define IA_HPP_

# include <string>

# include <boost/archive/binary_oarchive.hpp>
# include <boost/archive/binary_iarchive.hpp>
# include <boost/serialization/base_object.hpp>

# include "config.h"

extern "C" {
# include <lua.h>
# include <lualib.h>
# include <lauxlib.h>
}

# include "Fault.hpp"
# include "PMutex.hpp"
# include "PCondVar.hpp"
# include "PThread.hpp"
# include "APlayer.hpp"

class Ia : public APlayer
{
  friend class boost::serialization::access;

private:
  lua_State *_L;
  int _act;
  IThread *_thread;
  IMutex *_mutex;
  ICondVar *_condAct;
  bool _dead;
  bool _running;
  std::string _fileName;
  std::map<int, int> _actToSdlKey;

public:
  int getMap(int x, int y);
  const glm::vec2& getPos() const;

  void update(gdl::Input &input, gdl::Clock const &clock);
  void action(int act);
  void *init();
  bool nothing(UNUSED double const distance);
  const glm::vec2& getMapDimension() const;

public:
  template<class Archive>
  void serialize(Archive & ar, UNUSED const unsigned int version)
  {
    ar & boost::serialization::base_object<APlayer>(*this);
    ar & _act;
    ar & _dead;
    ar & _running;
    ar & _fileName;
  }

public:
  Ia(Map *currentMap, glm::vec2 const &pos, std::string const &fileName, const glm::vec4& color);
  ~Ia();

  int exec(); /*!BLOKING!, call when the ia can make one action */
};

#endif
