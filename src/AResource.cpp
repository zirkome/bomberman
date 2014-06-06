#include "ResourceManager.hpp"
#include "AResource.hpp"

AResource::AResource(const std::string& name)
: _name(name)
{
}

AResource::~AResource()
{
    ResourceManager::getInstance()->remove(_name);
}
