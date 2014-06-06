#ifndef _RESOURCEMANAGER_H_
# define _RESOURCEMANAGER_H_

#include <AResource.hpp>
#include <MediaManager.hpp>
//#include <Model.hpp>
//#include <ScatteredHierarchy.hpp>
#include <SharedPointer.hpp>
#include <Singleton.hpp>
#include <Texture.hpp>
//#include <TypeList.hpp>
#include <map>
#include <string>
#include <utility>

class AResource;
//template<class T>
//struct ResourceHolder
//{
//    typedef std::map<std::string, SharedPointer<T> > ResMap;
//    ResMap _resources;
//};
//
//typedef TYPELIST_2(Texture, Model) Resource;

class ResourceManager : public Singleton<ResourceManager>
{
    friend ResourceManager* Singleton<ResourceManager>::getInstance();
    friend void Singleton<ResourceManager>::kill();

public:
  template <class T> SharedPointer<T> get(const std::string& name);

  void add(const std::string& name, AResource* resource);

  void remove(const std::string& name);

private:
  ResourceManager();
  virtual ~ResourceManager();

private:
  typedef std::map<std::string, AResource* > ResMap_t;
  ResMap_t _resources;
};

inline void ResourceManager::add(const std::string& name, AResource* resource)
{
    _resources[name] = resource;
}

template<class T>
SharedPointer<T> ResourceManager::get(const std::string& name)
{
    ResMap_t::iterator it = _resources.find(name);

    if (it == _resources.end())
    {
        AResource* res = MediaManager::getInstance()->loadMediaFromFile<T>(name);
        add(name, res);
        return SharedPointer<T>(dynamic_cast<T*>(res));
    }
	return SharedPointer<T>(dynamic_cast<T*>(it->second));
}

#endif /* _RESOURCEMANAGER_H_ */
