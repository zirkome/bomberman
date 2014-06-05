#ifndef TEXTURELOADER_HPP_
#define TEXTURELOADER_HPP_

#include <string>
#include <Texture.hh>

#include "ILoader.hpp"
#include "SharedPointer.hpp"

class TextureLoader : public ILoader<gdl::Texture>
{
public:
    virtual SharedPointer<gdl::Texture> loadFromFile(const std::string& filename);
};


#endif /* TEXTURELOADER_HPP_ */
