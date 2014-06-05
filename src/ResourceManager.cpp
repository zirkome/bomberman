#include <string>
#include <MediaManager.hpp>
#include <ResourceManager.hpp>

void ResourceManager::add(const std::string& name, AResource* resource)
{
	_resources[name] = resource;
}

void ResourceManager::remove(const std::string& name)
{
	_resources.erase(name);
}

ResourceManager::ResourceManager()
{
    MediaManager::getInstance()->registerLoader(new TextureLoader, "tga");
    MediaManager::getInstance()->registerLoader(new ModelLoader, "obj,fbx,dae");
}

ResourceManager::~ResourceManager()
{
}
