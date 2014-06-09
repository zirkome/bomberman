#ifndef GEOMETRYLOADER_H
# define GEOMETRYLOADER_H

# include <string>

# include "config.h"
# include "ILoader.hpp"
# include "SharedPointer.hpp"
# include "AGeometry.hpp"

class GeometryLoader : public ILoader<AGeometry>
{
public:
  virtual AGeometry* loadFromFile(const std::string& filename);
};

#endif // GEOMETRYLOADER_H
