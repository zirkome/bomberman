#include <fstream>

#include "SaveManager.hpp"

void SaveManager::save(const std::list<ISerializable*>& data,
		       const std::string& filename)
{
  std::ofstream file(filename.c_str());

  for (SMListConstIterator it = data.begin(), end = data.end(); it != end; ++it)
    {
      (*it)->writeObject(file);
    }

  file.close();
}

void SaveManager::load(std::list<ISerializable*>& data,
		       const std::string& filename)
{
  std::ifstream file(filename.c_str());

  for (SMListConstIterator it = data.begin(), end = data.end(); it != end; ++it)
    {
      (*it)->readObject(file);
    }

  file.close();
}
