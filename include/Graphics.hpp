#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP

# include <iostream>
# include <exception>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Geometry.hh>
# include <Texture.hh>
# include <BasicShader.hh>
# include <Model.hh>

# include "FBORenderer.hpp"
# include "config.h"

/*
** Stock all the information needed to display
*/

class Graphics
{
public:
  virtual ~Graphics() {};

  virtual bool init(const glm::ivec2& win) = 0;
  virtual void startFrame() const = 0;

  virtual gdl::AShader *getShader() const = 0;
};

class IntroGraphics : public Graphics
{
public:
  IntroGraphics();
  virtual ~IntroGraphics();

  virtual bool init(const glm::ivec2& win);
  virtual void startFrame() const;

  void processFrame(const glm::vec3& camPos) const;

  gdl::AShader *getShader() const;

private:
  float _fov;
  glm::mat4 _proj;
  FBORenderer* _fbo;
};

class GameGraphics : public Graphics
{
public:
  GameGraphics();
  virtual ~GameGraphics();

  virtual bool init(const glm::ivec2& win);
  virtual void startFrame() const;

  void processFrame(const glm::vec3& camPos) const;

  gdl::AShader *getShader() const;

protected:
  float _fov;
  glm::mat4 _proj;
  FBORenderer* _fbo;
};

#endif
