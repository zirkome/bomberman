#include "ResourceManager.hpp"

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
}

ResourceManager::~ResourceManager()
{
}
