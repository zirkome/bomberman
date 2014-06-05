#ifndef MODELLOADER_HPP_
#define MODELLOADER_HPP_

#include <config.h>
#include <ILoader.hpp>
#include <Model.hpp>
#include <string>

class Model;

class ModelLoader : public ILoader<Model>
{
public:
    virtual bomberman::SPModel loadFromFile(const std::string& filename);
};



#endif /* MODELLOADER_HPP_ */
