#ifndef GAMEGEOMETRY_H
# define GAMEGEOMETRY_H

# include "AGeometry.hpp"
# include "AObject.hpp"
# include "SharedPointer.hpp"

class GameGeometry : public AObject
{
public:
  GameGeometry(const SharedPointer<AGeometry>& geo);
  GameGeometry(AGeometry* geo);
  virtual ~GameGeometry() {};

  virtual void draw(gdl::AShader *shader, const gdl::Clock& clock);

  AGeometry* operator->() const;
private:
  SharedPointer<AGeometry> _geo;
};

#endif // GAMEGEOMETRY_H
