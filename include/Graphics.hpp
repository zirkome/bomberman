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
  virtual ~Graphics() {};

  virtual bool init(const glm::ivec2& win) = 0;
  virtual void startFrame() = 0;

};

class MenuGraphics : public Graphics
{
public:
  MenuGraphics();
  virtual ~MenuGraphics();

  virtual bool init(const glm::ivec2& win);
  virtual void startFrame();

  gdl::AShader *getShader() {return _shader;};

private:
  gdl::AShader *_shader;
};

class GameGraphics : public Graphics
{
public:
  GameGraphics();
  virtual ~GameGraphics();

  virtual bool init(const glm::ivec2& win);
  virtual void startFrame();

  gdl::AShader *getShader() {return _shader;};

protected:
  float _fov;
  glm::mat4 _proj;
  gdl::AShader *_shader;
};

#endif
