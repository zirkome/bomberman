#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <exception>

#include <glm/glm.hpp>
#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include <Model.hh>

#include "ACamera.hpp"

/*
** Stock all the information needed to display
*/

class Graphics
{
public:
  Graphics();
  ~Graphics();

  bool init(const glm::vec2& win, float fov = 60.0);
  gdl::AShader *getShader();

  void startFrame();

protected:
  gdl::AShader *_shader;
  glm::mat4 _proj;
};

#endif
