#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <SdlContext.hh>
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

public:
  gdl::SdlContext context;
  gdl::BasicShader shader;
};

#endif
