#ifndef MEDIAMANAGER_HPP_
#define MEDIAMANAGER_HPP_

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <Texture.hh>

#include "Fault.hpp"
#include "Helper.hpp"
#include "ILoader.hpp"
#include "SharedPointer.hpp"
#include "Singleton.hpp"
#include "ScatteredHierarchy.hpp"

template<class T>
struct MediaHolder
{
    typedef std::map<std::string, SharedPointer<ILoader<T> > > LoadersMap;
    LoadersMap _loaders;
};

typedef TYPELIST_1(gdl::Texture) Medias;

class MediaManager: public Singleton<MediaManager>,
                    public ScatteredHierarchy<Medias, MediaHolder>
{
    friend MediaManager* Singleton<MediaManager>::getInstance();
    friend void Singleton<MediaManager>::kill();

public:
    template<class T>
    inline ILoader<T>& findLoader(const std::string& filename)
    {
        std::string extension = filename.substr(filename.find_last_of(".") + 1);
        std::transform(extension.begin(), extension.end(), extension.begin(),
                        ::tolower);

        typename MediaHolder<T>::LoadersMap::iterator it = MediaHolder<T>::_loaders.find(extension);

        if (it != MediaHolder<T>::_loaders.end())
            return *it->second;
        throw nFault("No such loader for this type of file.");
    }

    template<class T>
    inline void registerLoader(ILoader<T>* loader,
                    const std::string& extensions)
    {
        std::vector<std::string> ext;
        split(extensions, " /\\*.,;|-_\t\n'\"", ext);

        SharedPointer<ILoader<T> > ptr = loader;
        for (std::vector<std::string>::iterator i = ext.begin(), end =
                        ext.end(); i != end; ++i)
        {
            std::transform(i->begin(), i->end(), i->begin(), ::tolower);
            MediaHolder < T > ::_loaders[*i] = ptr;
        }
    }

private:
    MediaManager();
    virtual ~MediaManager();
};

#endif /* MEDIAMANAGER_HPP_ */
