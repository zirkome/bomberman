#ifndef MODELLOADER_HPP_
#define MODELLOADER_HPP_

#include "Model.hpp"

class ModelLoader : public ILoader<Model> {
public:
    virtual bomberman::SPModel loadFromFile(const std::string& filename);
};



#endif /* MODELLOADER_HPP_ */
