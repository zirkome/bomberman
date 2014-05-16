#ifndef _ASSETSMANAGER_H_
# define _ASSETSMANAGER_H_

# include <iostream>
# include <exception>
# include <stdexcept>
# include <map>
# include <Texture.hh>
# include <Model.hh>

# include "config.h"
# include "IEntity.hpp"

class		AssetsManager
{
private:
  std::map<IEntity::Type, gdl::Texture *>	_textures;
  std::map<IEntity::Type, gdl::Model *>		_model;

public:
  AssetsManager() {}
  virtual ~AssetsManager();
  static AssetsManager	*getInstance();
  static void		createAssets();
  template <class T>
  void loadAssets(std::string const &, IEntity::Type) {}

  template <class T>
  T *getAssets(IEntity::Type)
  {
    return NULL;
  }

  static AssetsManager	*_instance;
};

#endif /* _ASSETSMANAGER_H_ */
