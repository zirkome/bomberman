#ifndef AGEOMETRY_H
# define AGEOMETRY_H

# include <Geometry.hh>

# include "AResource.hpp"

class AGeometry : public gdl::Geometry, public AResource
{
public:
  explicit AGeometry(const std::string &geoName);
  virtual ~AGeometry() {};
};

#endif // AGEOMETRY_H
