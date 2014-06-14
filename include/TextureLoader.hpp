#ifndef TEXTURELOADER_HPP_
# define TEXTURELOADER_HPP_

# include <string>

# include "config.h"
# include "ILoader.hpp"
# include "SharedPointer.hpp"
# include "Texture.hpp"

class TextureLoader : public ILoader<Texture>
{
public:
  virtual Texture* loadFromFile(const std::string& filename) const;
};


#endif /* TEXTURELOADER_HPP_ */
