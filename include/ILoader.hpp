#ifndef ILOADER_HPP_
# define ILOADER_HPP_

# include "SharedPointer.hpp"

template <class T>
class ILoader
{
public:
  virtual ~ILoader() {}

public:
  virtual T* loadFromFile(const std::string& filename) = 0;
//    virtual void saveToFile(const T* object, const std::string& filename) = 0;
};

#endif /* ILOADER_HPP_ */
