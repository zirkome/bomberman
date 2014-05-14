#ifndef _CUBE_H_
#define _CUBE_H_

#include "AObject.hpp"
#include <Texture.hh>
#include <Geometry.hh>
#include <iostream>

class Cube : public AObject
{
private:
  // La texture utilisee pour le cube
  gdl::Texture _texture;
  // La geometrie du cube
  gdl::Geometry _geometry;
  // La vitesse de deplacement du cube
  float _speed;
public:
  Cube();
  virtual ~Cube();
  virtual bool	initialize();
  // La fonction update sert a gerer le comportement de l'objet
  virtual void	update(gdl::Clock const &clock, gdl::Input &input);
  // La fonction draw sert a dessiner l'objet
  virtual void	draw(gdl::AShader *shader);
};

#endif /* _CUBE_H_ */
