#ifndef _RESOURCEMANAGER_H_
# define _RESOURCEMANAGER_H_

#include <map>
#include <string>
#include <utility>

#include <MediaManager.hpp>
#include <SharedPointer.hpp>
#include <Singleton.hpp>
#include <AResource.hpp>

class ResourceManager : public Singleton<ResourceManager>
{
    friend ResourceManager* Singleton<ResourceManager>::getInstance();
    friend void Singleton<ResourceManager>::kill();

public:
  template <class T> SharedPointer<T> get(const std::string& name) const;

  void add(const std::string& name, AResource *resource);

  void remove(const std::string& name);

private:
  ResourceManager();
  virtual ~ResourceManager();

private:
  typedef std::map<std::string, SharedPointer<AResource> > ResMap_t;
  std::map<std::string, SharedPointer<AResource> > _resources;
};

template<class T>
inline SharedPointer<T> ResourceManager::get(const std::string& name) const
{
    SharedPointer<T> res = null_ptr;
    ResMap_t::iterator it = _resources.find(name);

    if (it == _resources.end())
    {
        SharedPointer<T> res =
                        MediaManager::getInstance()->loadMediaFromFile<T>(name);
        ResourceManager::getInstance()->add(name, res);
        return res;
    }
	return *it->second;
}

#endif /* _RESOURCEMANAGER_H_ */
