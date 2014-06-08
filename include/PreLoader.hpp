#ifndef PRELOADER_H
# define PRELOADER_H

# include <list>

# include "Singleton.hpp"
# include "SharedPointer.hpp"

class PreLoader : public Singleton<PreLoader>
{
public:
  friend PreLoader* Singleton<PreLoader>::getInstance();
  friend void Singleton<PreLoader>::kill();

  void addRessource(const SharedPointer<void*>& ptr);

private:
  explicit PreLoader();
  ~PreLoader();

  std::list<SharedPointer<void*> >_resList;
};

#endif // PRELOADER_H
