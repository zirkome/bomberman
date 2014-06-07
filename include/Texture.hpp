#ifndef TEXTURE_HPP_
# define TEXTURE_HPP_

class Texture;

# include <Texture.hh>

# include "AResource.hpp"

class Texture : public gdl::Texture,
                public AResource
{
public:
    Texture(const std::string &path);
    virtual ~Texture() {};

public:
    void bind() const;

};

#endif /* TEXTURE_HPP_ */
