#ifndef GEOMETRYLOADER_H
# define GEOMETRYLOADER_H

# include <string>
# include <map>

# include "config.h"
# include "ILoader.hpp"
# include "SharedPointer.hpp"
# include "AGeometry.hpp"

class GeometryLoader : public ILoader<AGeometry>
{
public:
  GeometryLoader();

  virtual AGeometry* loadFromFile(const std::string& type) const;

private:
  template<class T>
  AGeometry* instanciateGeometry() const;

private:
  std::map<std::string, AGeometry* (GeometryLoader::*)() const> _funcMap;
};

template<class T>
AGeometry* GeometryLoader::instanciateGeometry() const
{
  return new T;
}

#endif // GEOMETRYLOADER_H
