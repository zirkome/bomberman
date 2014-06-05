#ifndef TEXTURELOADER_HPP_
#define TEXTURELOADER_HPP_

#include <string>

#include "config.h"
#include "ILoader.hpp"
#include "SharedPointer.hpp"
#include "Texture.hpp"

class TextureLoader : public ILoader<Texture>
{
public:
    virtual bomberman::SPTexture loadFromFile(const std::string& filename);
};


#endif /* TEXTURELOADER_HPP_ */
