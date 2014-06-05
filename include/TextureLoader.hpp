#ifndef TEXTURELOADER_HPP_
#define TEXTURELOADER_HPP_

#include <string>
#include <Texture.hh>

#include "config.h"
#include "ILoader.hpp"
#include "SharedPointer.hpp"

class TextureLoader : public ILoader<gdl::Texture>
{
public:
    virtual bomberman::Texture loadFromFile(const std::string& filename);
};


#endif /* TEXTURELOADER_HPP_ */
