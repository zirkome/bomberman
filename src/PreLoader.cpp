#include "PreLoader.hpp"

PreLoader::PreLoader()
{
}

PreLoader::~PreLoader()
{
}

void PreLoader::addRessource(const SharedPointer<void*>& ptr)
{
  _resList.push_back(ptr);
}
