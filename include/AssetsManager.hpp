#ifndef _ASSETSMANAGER_H_
# define _ASSETSMANAGER_H_

# include <iostream>
# include <exception>
# include <stdexcept>
# include <map>
# include <Texture.hh>
# include <Model.hh>

# include "Model.hpp"
# include "config.h"
# include "AObject.hpp"
# include "IEntity.hpp"
# include "Singleton.hpp"

class AssetsManager : public Singleton<AssetsManager>
{
  friend AssetsManager* Singleton<AssetsManager>::getInstance();
  friend void Singleton<AssetsManager>::kill();

public:
  template <class T>
  void loadAssets(std::string const &, IEntity::Type) {};

  template <class T>
  T *getAssets(IEntity::Type)
  {
    return NULL;
  }

public:
  static void createAssets();

private:
  AssetsManager() {}
  virtual ~AssetsManager();


private:
  std::map<IEntity::Type, gdl::Texture *> _textures;
  std::map<IEntity::Type, Model *> _model;
};

#endif /* _ASSETSMANAGER_H_ */
