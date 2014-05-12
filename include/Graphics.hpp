#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <exception>

#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include <Model.hh>

/*
** Stock all the information needed to display
*/

class Graphics
{
public:
  Graphics();
  ~Graphics();

  bool init();

private:
  gdl::AShader *_shader;
};

#endif
