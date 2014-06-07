#ifndef MODELLOADER_HPP_
# define MODELLOADER_HPP_

# include <string>

# include "config.h"
# include "ILoader.hpp"
# include "Model.hpp"

class Model;

class ModelLoader : public ILoader<Model>
{
public:
    virtual Model* loadFromFile(const std::string& filename);
};



#endif /* MODELLOADER_HPP_ */
