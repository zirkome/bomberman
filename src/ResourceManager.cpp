#include "ModelLoader.hpp"
#include "ResourceManager.hpp"
#include "TextureLoader.hpp"
#include "GeometryLoader.hpp"

void ResourceManager::remove(const std::string& name)
{
  _resources.erase(name);
}

ResourceManager::ResourceManager()
{
  MediaManager::getInstance()->registerLoader(new TextureLoader, "tga");
  MediaManager::getInstance()->registerLoader(new ModelLoader, "obj,fbx,dae");
  MediaManager::getInstance()->registerLoader(new GeometryLoader, "geo");
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::add(const std::string& name, SharedPointer<AResource> resource)
{
  _resources[name] = resource;
}
