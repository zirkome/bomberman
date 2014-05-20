#include "AssetsManager.hpp"

AssetsManager::~AssetsManager()
{

}

template <>
void AssetsManager::loadAssets<gdl::Texture>(const std::string &path, IEntity::Type assetsType)
{
  gdl::Texture	*ptr;

  ptr = new gdl::Texture;
  if (ptr->load(path) == false)
    {
      throw std::runtime_error("Can't load texture : " + path);
    }
  _textures[assetsType] = ptr;
  std::cout << path + " has been loaded" << std::endl;
}

template <>
void AssetsManager::loadAssets<gdl::Model>(const std::string &path, IEntity::Type assetsType)
{
  gdl::Model	*ptr;

  ptr = new gdl::Model;
  if (ptr->load(path) == false)
    {
      throw std::runtime_error("Can't load model : " + path);
    }
  _model[assetsType] = ptr;
}

template <>
gdl::Texture *AssetsManager::getAssets<gdl::Texture>(IEntity::Type assetsType)
{
  std::map<IEntity::Type, gdl::Texture *>::iterator it = _textures.find(assetsType);

  if (it == _textures.end())
    {
      return NULL;
    }
  return (it->second);
}

template <>
gdl::Model *AssetsManager::getAssets<gdl::Model>(IEntity::Type assetsType)
{
  std::map<IEntity::Type, gdl::Model *>::iterator it = _model.find(assetsType);

  if (it == _model.end())
    {
      return NULL;
    }
  return (it->second);
}

void AssetsManager::createAssets()
{
  AssetsManager *obj = AssetsManager::getInstance();

  obj->loadAssets<gdl::Texture>(RES_ASSETS "wall_texture.tga", IEntity::WALL);
  obj->loadAssets<gdl::Texture>(RES_ASSETS "box_texture.tga", IEntity::BOX);
  obj->loadAssets<gdl::Texture>(RES_ASSETS "ground_texture.tga", IEntity::GROUND);
}
