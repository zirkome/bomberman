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
void AssetsManager::loadAssets<Model>(const std::string &path, IEntity::Type assetsType)
{
  Model	*ptr;

  ptr = new Model(path);
  _model[assetsType] = ptr;
  std::cout << path + " has been loaded" << std::endl;
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
Model *AssetsManager::getAssets<Model>(IEntity::Type assetsType)
{
  std::map<IEntity::Type, Model *>::iterator it = _model.find(assetsType);

  if (it == _model.end())
    {
      return NULL;
    }
  return (it->second);
}

void AssetsManager::createAssets()
{
  AssetsManager *obj = AssetsManager::getInstance();

  obj->loadAssets<gdl::Texture>(RES_TEXTURE "wall_texture.tga", IEntity::WALL);
  // obj->loadAssets<gdl::Texture>(RES_TEXTURE "brick_wall.tga", IEntity::WALL);
  obj->loadAssets<gdl::Texture>(RES_TEXTURE "box_texture.tga", IEntity::BOX);
  obj->loadAssets<gdl::Texture>(RES_TEXTURE "ground_texture.tga", IEntity::GROUND);
  obj->loadAssets<gdl::Texture>(RES_TEXTURE "bomberman.tga", IEntity::LOGO);
  obj->loadAssets<gdl::Texture>(RES_TEXTURE "skybox.tga", IEntity::SKYBOX);
  obj->loadAssets<Model>(RES_MODEL "marvin.fbx", IEntity::PLAYER);
  obj->loadAssets<Model>(RES_MODEL "bomb.fbx", IEntity::BOMB);
}
