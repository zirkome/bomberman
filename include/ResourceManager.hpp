#ifndef _RESOURCEMANAGER_H_
# define _RESOURCEMANAGER_H_

# include <map>
# include "Singleton.hpp"
# include "AResource.hpp"

class ResourceManager : public Singleton<ResourceManager>
{
public:
  template <class T> T* get(const std::string& name) const;

  void add(const std::string& name, AResource *resource);

  void remove(const std::string& name);

private:
  ResourceManager();
  virtual ~ResourceManager();

private:
  std::map<std::string, AResource*> _resources;
};

template<class T>
inline T* ResourceManager::get(const std::string& name) const
{
	return _resources.at(name);
}

#endif /* _RESOURCEMANAGER_H_ */
